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
#include <jvb/binding/fill_class_file_context.hpp>
#include <jvb/binding/placeholder/method.hpp>
#include <jvb/class_file/generate_class_file.hpp>
#include <jvb/class_file/class_.hpp>

#include <boost/proto/proto.hpp>

#include <fstream>

namespace jvb {

namespace bind_placeholders {

using namespace jvb::binding::placeholder;

struct public_tag {};

boost::proto::terminal<public_tag>::type public_ = {{}};

}

struct constructor
{
  typedef void result_type;
  result_type operator()(environment, Object) const
  {
    std::cout << "default-constructor" << std::endl;
  }
};

template <typename C, typename Expr>
void bind_class(environment e, const char* name, Expr const& expr)
{
  typedef jvb::object base_class_type;

  class_files::class_ cf(name);

  // create default-constructor
  class_files::not_implemented_method init
    = { "<init>", "()V" };
  cf.not_implemented_methods.push_back(init);

  binding::fill_class_file_context ctx(cf);
  boost::proto::eval(expr, ctx);

  std::string class_file;
  class_files::generate_class_file(cf, std::back_inserter<std::string>(class_file));
  std::cout << "class_file size " << class_file.size() << std::endl;

  {
    std::ofstream file("HelloWorld.class");
    std::copy(class_file.begin(), class_file.end(), std::ostream_iterator<char>(file));
  }

  if(e.raw()->DefineClass(name, 0, reinterpret_cast<const jbyte*>(class_file.c_str())
                          , class_file.size()))
  {
    std::cout << "Success loading class" << std::endl;

    jvb::Class cls(e, name);
    jvb::bind_function<void(jvb::environment, jvb::Object), constructor>
      (e, cls, "<init>");
    
  }
  else
  {
    std::cout << "Failed loading class" << std::endl;
    e.raw()->ExceptionDescribe();
  }
}

}

#endif
