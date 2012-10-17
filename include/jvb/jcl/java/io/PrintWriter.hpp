// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_IO_PRINTWRITER_HPP
#define JVB_JCL_JAVA_IO_PRINTWRITER_HPP

#include <jvb/environment.hpp>
#include <jvb/class.hpp>
#include <jvb/object.hpp>
#include <jvb/field.hpp>
#include <jvb/method.hpp>
#include <jvb/string.hpp>

namespace jvb { namespace jcl { namespace java { namespace io {

struct PrintWriter_class : extends<PrintWriter_class, Class>
{
  PrintWriter_class(environment e, const char* name = "java/io/PrintWriter"))
    : Class(e, name)
  {}
};

struct PrintWriter : Object
{
  typedef PrintWriter_class class_type;

  PrintWriter()
  {
  }
  explicit PrintWriter(environment e, jobject obj)
    : Object(obj), println(e, raw(), "println")
  {
    assert(obj != 0);
  }

  method<void(jvb::string)> println;
};

} } } }

#endif
