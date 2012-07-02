// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/javabind.hpp>
#include <jvb/jcl/java/lang/System.hpp>

int main()
{
  jvb::jvm jvm;
  jvb::env env = jvm.env();

  jvb::ref<jvb::java::lang::Exception> exception
    = jvb::new_<jvb::java::lang::Exception>("Some reason");
  jvb::throw_(exception);
}
