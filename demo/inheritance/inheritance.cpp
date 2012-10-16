
#include <jvb/jvb.hpp>

#include <boost/functional/overloaded_function.hpp>
#include <boost/mpl/vector.hpp>

struct Writer_class
  : jvb::extends<jvb::jcl::java::lang::Class>
{
  Writer_class(jvb::environment e)
    : class_(e, "java/io/Writer")
  {}
};

struct Writer : jvb::jcl::java::lang::Object
{
  typedef Writer_class class_type;

  Writer(jvb::environment e, jobject obj)
    : object(obj)
    , close(e, obj, "close")
    , flush(e, obj, "flush")
  {}

  jvb::method<void()> close;
  jvb::method<void()> flush;
};

struct PrintWriter_class : jvb::extends<Writer_class>
{
  PrintWriter_class(jvb::environment e)
    : class_(e, "java/io/PrintWriter")
  {}
};

struct PrintWriter : Writer
{
  typedef PrintWriter_class class_type;

  PrintWriter(jvb::environment e, jobject obj)
    : Writer(e, obj)
    , println(jvb::method_overload<sequence_overload>(e, obj, "println"))
    , print(jvb::method_overload<sequence_overload>(e, obj, "print"))
    , checkError(e, obj, "checkError")
  {}

  typedef boost::overloaded_function
  <void(), void(bool), void(jvb::char_), void(jvb::array<jvb::char_>)
    , void(jvb::double_), void(jvb::float_), void(jvb::int_), void(jvb::long_)
   , void(jvb::object), void(jvb::string)> overload_function;
  typedef boost::mpl::vector10
  <void(), void(bool), void(jvb::char_), void(jvb::array<jvb::char_>)
    , void(jvb::double_), void(jvb::float_), void(jvb::int_), void(jvb::long_)
   , void(jvb::object), void(jvb::string)> sequence_overload;

  overload_function println;
  overload_function print;
  jvb::method<bool()> checkError;
};

struct System_class : jvb::extends<jvb::jcl::java::lang::Class>
{
  System_class(jvb::environment e)
    : class_(e, "java/lang/System")
    , out(e, *this, "out")
  {}

  jvb::static_field<PrintWriter> out;
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
  system.out.println("Hello World");
}
