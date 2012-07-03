
#include <jvb/jvb.hpp>

#include <jni.h>

#include <iostream>

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
  jvb::jvm jvm(vm);
  std::cout << "JNI_OnLoad" << std::endl;
  return JNI_VERSION_1_2;
}

