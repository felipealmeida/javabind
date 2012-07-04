
#include <jvb/jvb.hpp>
#include <jvb/bind_function.hpp>

#include <jni.h>

#include <iostream>

struct print
{
  void operator()(jvb::environment e, jvb::Object self)
  {
    std::cout << "Hello World from C++" << std::endl;
  }
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
  jvb::jvm jvm(vm);
  jvb::environment env = jvm.environment();
  std::cout << "JNI_OnLoad" << std::endl;

  jvb::Class c(env, "CallingCppLibrary");
  jvb::bind_function<void(jvb::environment, jvb::Object), ::print>(env, c, "print");

  return JNI_VERSION_1_2;
}

