
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
