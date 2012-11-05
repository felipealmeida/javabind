// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>
#include <jvb/jcl/java/lang/System.hpp>

#include <jni.h>

#include <cstdlib>

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.environment();

  jvb::jcl::java::lang::System::out(env)().println()(env, jvb::string(env, "Hello World"));
}
