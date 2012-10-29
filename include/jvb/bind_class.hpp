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
    }
  }
};

template <typename C, typename P, typename Allocator, typename Expr>
Class bind_class(environment e, Expr const& expr)
{
  class_files::class_ cf(C::name());

  // create default-constructor
  
  cf.not_implemented_methods.push_back
    (class_files::name_descriptor_pair("<init>", "()V"));

  cf.static_fields.push_back
    (class_files::name_descriptor_pair("javabind_vtable", "J"));

  typedef boost::fusion::vector<class_files::class_&, environment> populate_data_type;
  binding::populate_class_file_transform populate_transform;
  populate_data_type populate_data (cf, e);
  populate_transform(expr, binding::virtual_table<0>(), populate_data);

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
    std::string filename (C::name());
    filename += ".class";
    std::ofstream file(filename.c_str());
    std::copy(class_file.begin(), class_file.end(), std::ostream_iterator<char>(file));
  }

  if(jclass cls_raw = e.raw()->DefineClass(C::name(), 0, reinterpret_cast<const jbyte*>(&class_file[0])
                                       , class_file.size()))
  {
    std::cout << "Success loading class" << std::endl;

    jvb::Class cls(cls_raw);

    typedef typename boost::result_of
      <binding::count_virtual_table_transform(Expr, boost::mpl::size_t<0>)>::type
      virtual_table_size;

    typedef binding::virtual_table<virtual_table_size::value> virtual_table_type;
    std::auto_ptr<virtual_table_type>
      virtual_table(new virtual_table_type);
    typedef boost::fusion::vector<Class&, environment, virtual_table_type&> binding_data_type;

    binding::bind_functions_transform<P> bind_transform;
    binding_data_type binding_data (cls, e, *virtual_table);
    bind_transform(expr, boost::mpl::size_t<0>(), binding_data);

    jvb::bind_function<void(jvb::environment, jvb::Object)
                       , constructor<P, Allocator> >
      (e, cls, "<init>");

    {
      ::jlong rl = 0;
      void* p = virtual_table.release();
      std::memcpy(&rl, &p, sizeof(void*));
      const char* d = "J";
      ::jclass c = cls.raw();
      assert(c != 0);
      jfieldID fid = e.raw()->GetStaticFieldID
        (c, "javabind_vtable", d);
      assert(fid != 0);
      e.raw()->SetStaticLongField(c, fid, rl);
    }

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

template <typename C, typename P, typename Expr>
Class bind_class(environment e, Expr const& expr)
{
  return bind_class<C, P, std::allocator<C> >(e, expr);
}

}

#endif
