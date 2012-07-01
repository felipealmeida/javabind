
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

struct PrintWriter_peer : jvb::self<PrintWriter>
{
  void println_string(jvb::string string) const
  {
    std::cout << string << std::endl;
  }
  void print_string(jvb::string string) const
  {
    std::cout << string << std::endl;
  }
  void function(jvb::environment e, jvb::int_ x)
  {
  }
};

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.env();

  {
    using namespace jvb::structure;

    jvb::define_peer<PrintWriter_peer>(e)
      [
       constructor<void()>()
       , method(&PrintWriter::println, &PrintWriter_peer::println_string
                , &PrintWriter_peer::println_char, &PrintWriter_peer::println_char)
       , method<void()>("somethingElse")
      ];
  }
}
