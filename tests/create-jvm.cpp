// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#define BOOST_TEST_MODULE create_jvm
#include <boost/test/included/unit_test.hpp>

#include <jni.h>

BOOST_AUTO_TEST_CASE (create_jvm)
{
  JavaVMInitArgs vm_args;
  vm_args.version = 0x00010002;
  vm_args.nOptions = 0;
  vm_args.ignoreUnrecognized = JNI_TRUE;
  JavaVM* jvm = 0;
  JNIEnv* env_ = 0;
  int res = JNI_CreateJavaVM(&jvm, (void**)&env_, &vm_args);
  BOOST_REQUIRE(res >= 0);
}
