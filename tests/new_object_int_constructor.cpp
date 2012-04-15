// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

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
  javabind::constructor<javabind::object(jint)> constructor
    = cls.constructor<javabind::object(jint)>();
  javabind::object object = constructor(cls, 5);
}
