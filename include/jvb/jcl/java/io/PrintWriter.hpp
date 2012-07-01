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

namespace jvb { namespace jcl { namespace java { namespace io {

struct PrintWriter_class : Class
{
  
};

struct PrintWriter : Object
{
  PrintWriter() {}
  explicit PrintWriter(jobject obj)
    : Object(obj)
  {
  }

  void println(environment e, const char* c) const {}
};

} } } }

#endif
