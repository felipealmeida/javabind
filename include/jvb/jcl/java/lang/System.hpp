// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_LANG_SYSTEM_HPP
#define JVB_JCL_JAVA_LANG_SYSTEM_HPP

#include <jvb/jcl/java/io/PrintStream.hpp>
#include <jvb/environment.hpp>
#include <jvb/class.hpp>
#include <jvb/object.hpp>
#include <jvb/static_field.hpp>

namespace jvb { namespace jcl { namespace java { namespace lang {

struct System_class : extends<System_class, Class>
{
  System_class(environment e, const char* name = "java/lang/System")
    : base_type(e, name)
    , out(e, *this, "out")
  {}

  static_field<java::io::PrintStream> out;
};

struct System
{
  typedef System_class class_type;
};

} } } }

#endif
