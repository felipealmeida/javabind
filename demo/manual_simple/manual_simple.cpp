
#include <jvb/javabind.hpp>

struct PrintWriter_class : jvb::class_
{
  PrintWriter(jvb::env e)
    : class_(e, "java/io/PrintWriter")
  {}
};

struct PrintWriter : jvb::object
{
  typedef PrintWriter_class class_type;

  PrintWriter(jvb::env e)
    : object(class_type(e))
    , println(this, "println")
    , print(this, "print")
    , checkError(this, "checkError")
    , close(this, "close")
    , flush(this, "flush")
  {}

  typedef boost::mpl::vector10
  <void(), void(bool), void(jvb::char_), void(jvb::array<jvb::char_>)
    , void(jvb::double_), void(jvb::float_), void(jvb::int_), void(jvb::long_)
   , void(jvb::object), void(jvb::string)> signature_sequence;

  jvb::overload<signature_sequence> println;
  jvb::overload<signature_sequence> print;
  jvb::method<bool()> checkError;
  jvb::method<void()> close;
  jvb::method<void()> flush;
};

struct System_class : jvb::class_
{
  System(jvb::env e)
    : class_(e, "java/lang/System"), out(this, "out")
  {}

  jvb::static_field<PrintWriter> out;
};

struct System : jvb::object
{
  typedef system_class class_type;

  System(jvb::env e)
    : class_(class_type(e))
  {}
};

int main()
{
  jvb::jvm jvm;
  jvb::env env = jvm.env();

  system_class system(env);
  system.out.println("Hello World");
}
