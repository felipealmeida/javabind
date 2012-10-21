// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BIND_CLASS_HPP
#define JVB_BIND_CLASS_HPP

#include <jvb/jvb.hpp>
#include <jvb/bind_function.hpp>
#include <jvb/detail/create_signature.hpp>
#include <jvb/binding/bind_functions_transform.hpp>
#include <jvb/binding/populate_class_file_transform.hpp>
#include <jvb/binding/method.hpp>
#include <jvb/class_file/class_file_generator.hpp>
#include <jvb/class_file/generate_class_file.hpp>
#include <jvb/class_file/class_.hpp>

#include <boost/proto/proto.hpp>

#include <fstream>

namespace jvb {

namespace bind_placeholders {

using jvb::binding::method;

struct public_tag {};

boost::proto::terminal<public_tag>::type public_ = {{}};

}

template <typename T, typename Allocator>
struct constructor
{
  typedef void result_type;
  result_type operator()(environment e, Object obj) const
  {
    assert(obj.raw() != 0);
    BOOST_MPL_ASSERT((boost::mpl::bool_<(sizeof(void*) <= sizeof(::jlong))>));
    typename Allocator::template rebind<T>::other allocator;
    std::cout << "default-constructor" << std::endl;
    void* p = allocator.allocate(1, 0);
    T* object = new (p) T;
    p = static_cast<void*>(object);
    ::jlong rl = 0;
    std::memcpy(&rl, &p, sizeof(void*));
    jvb::long_ l(rl);
    {
      const char* d = "J";
      ::jclass cls = obj.class_(e).raw();
      assert(cls != 0);
      jfieldID fid = e.raw()->GetStaticFieldID
        (cls, "javabind_vtable", d);
      assert(fid != 0);
      e.raw()->SetStaticLongField(cls, fid, l);
    }
  }
};

template <typename C, typename Allocator, typename Expr>
Class bind_class(environment e, const char* name, Expr const& expr)
{
  assert(name != 0);
  typedef jvb::object base_class_type;

  class_files::class_ cf(name);

  // create default-constructor
  
  cf.not_implemented_methods.push_back
    (class_files::name_descriptor_pair("<init>", "()V"));

  cf.static_fields.push_back
    (class_files::name_descriptor_pair("javabind_vtable", "J"));

  boost::mpl::size_t<0u> first;
  binding::populate_class_file_transform populate_transform;
  boost::fusion::vector<class_files::class_&, environment> data (cf, e);
  populate_transform(expr, first, data);

  class_files::class_file_generator<std::back_insert_iterator<std::vector<char> > >
    class_file_generator;
  std::vector<char> class_file;
  namespace karma = boost::spirit::karma;
  if(!karma::generate(std::back_inserter(class_file)
                      , class_file_generator(0x21)[karma::_1 = cf]))
  {
    throw std::runtime_error("Failed generating class file");
  }
  std::cout << "class_file size " << class_file.size() << std::endl;

  {
    std::string filename (name);
    filename += ".class";
    std::ofstream file(filename.c_str());
    std::copy(class_file.begin(), class_file.end(), std::ostream_iterator<char>(file));
  }

  if(e.raw()->DefineClass(name, 0, reinterpret_cast<const jbyte*>(&class_file[0])
                          , class_file.size()))
  {
    std::cout << "Success loading class" << std::endl;

    jvb::Class cls(e, name);

    boost::fusion::vector<Class&, environment> data (cls, e);
    binding::bind_functions_transform bind_transform;
    bind_transform(expr, first, data);

    jvb::bind_function<void(jvb::environment, jvb::Object)
                       , constructor<C, Allocator> >
      (e, cls, "<init>");

    std::cout << "Success binding the method" << std::endl;

    return cls;
  }
  else
  {
    std::cout << "Failed defining class" << std::endl;
    e.raw()->ExceptionDescribe();
    throw std::runtime_error("Couldn't define class");
  }
}

template <typename C, typename Expr>
Class bind_class(environment e, const char* name, Expr const& expr)
{
  return bind_class<C, std::allocator<C>, Expr>(e, name, expr);
}

}

#endif
