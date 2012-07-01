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

struct PrintWriter_class : Class
{
  
};

struct PrintWriter : Object
{
  PrintWriter()
    : println(raw(), "println")
  {
  }
  explicit PrintWriter(jobject obj)
    : Object(obj), println(raw(), "println")
  {
    assert(obj != 0);
  }

  method<void(jvb::string)> const println;
};

} } } }

#endif
