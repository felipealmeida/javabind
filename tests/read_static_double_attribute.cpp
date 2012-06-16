// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <javabind/env.hpp>
#include "load_file_class.hpp"

#include <jni.h>

#include <cstdlib>

int main(int argc, char* argv[])
{
  assert(argc == 2);
  JavaVMInitArgs vm_args;
  vm_args.version = 0x00010002;
  vm_args.nOptions = 0;
  vm_args.ignoreUnrecognized = JNI_TRUE;
  JavaVM* jvm = 0;
  javabind::env env;
  {
    JNIEnv* env_ = 0;
    int res = JNI_CreateJavaVM(&jvm, (void**)&env_, &vm_args);
    if(!(res >= 0))
      std::abort();
    env = javabind::env(env_);
  }

  javabind::class_ cls = load_file_class(argv[1], env);
  javabind::static_field<jdouble> field = cls.static_field<jdouble>("attribute");
  jdouble attribute = field.get(cls);
  if(attribute != 15)
    std::abort();
}
