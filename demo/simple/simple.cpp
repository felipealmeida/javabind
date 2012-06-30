
#include <jvb/javabind.hpp>
#include <jvb/jcl/java/lang/System.hpp>

int main()
{
  jvb::jvm jvm;
  jvb::env env = jvm.env();

  jvb::local_ref<jvb::java::lang::System::class_type> system;
  jvb::ref<jvb::java::lang::System::class_type> system;
  jvb::global_ref<jvb::java::lang::System::class_type> system;
  system->out.println(env, "Hello World");
}
