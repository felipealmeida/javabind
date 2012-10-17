
#include <jvb/jvb.hpp>

#include <boost/functional/overloaded_function.hpp>
#include <boost/mpl/vector.hpp>

struct FilterOutputStream_class
  : jvb::extends<FilterOutputStream_class, jvb::jcl::java::lang::Class>
{
  FilterOutputStream_class(jvb::environment e, const char* name = "java/io/FilterOutputStream")
    : base_type(e, name)
  {}
};

struct FilterOutputStream : jvb::jcl::java::lang::Object
{
  typedef FilterOutputStream_class class_type;

  FilterOutputStream(jvb::environment e, jobject obj)
    : object(obj)
    , close(e, obj, "close")
    , flush(e, obj, "flush")
  {}

  jvb::method<void()> close;
  jvb::method<void()> flush;
};

struct PrintStream_class : jvb::extends<PrintStream_class, FilterOutputStream_class>
{
  PrintStream_class(jvb::environment e)
    : base_type(e, "java/io/PrintStream")
  {}
};

struct PrintStream : FilterOutputStream
{
  typedef PrintStream_class class_type;

  typedef jvb::method_overload
  <void(bool)
   , void(jvb::char_)
   , void(jvb::array<jvb::char_>)
   , void(jvb::double_)
   , void(jvb::float_)
   , void(jvb::int_)
   , void(jvb::long_)
   , void(jvb::object)
   , void(jvb::string)
  > print_overload;

  PrintStream(jvb::environment e, jobject obj)
    : FilterOutputStream(e, obj)
    , println(e, obj, "println")
    , print(e, obj, "print")
    , checkError(e, obj, "checkError")
  {}

  print_overload println;
  print_overload print;
  jvb::method<bool()> checkError;
};

struct System_class : jvb::extends<System_class, jvb::jcl::java::lang::Class>
{
  System_class(jvb::environment e)
    : base_type(e, "java/lang/System")
    , out(e, *this, "out")
  {}

  jvb::static_field<PrintStream> out;
};

struct System : jvb::jcl::java::lang::Object
{
  typedef System_class class_type;

  System(jvb::environment e, jobject obj)
    : object(obj)
  {}
};

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.environment();

  System_class system(env);
  system.out.println(env, "Hello World");
}
