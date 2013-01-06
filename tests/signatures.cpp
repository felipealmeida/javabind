// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

JVB_ADAPT_CLASS((jvb)(tests)(Signatures)
                , (public)
                , (methods
                   (foo1, void(), nil)
                   (foo2, void(boolean), nil)
                   (foo3, void(boolean(&)[2]), nil)
                   (foo4, void(byte), nil)
                   (foo5, void(byte(&)[2]), nil)
                   (foo6, void(char), nil)
                   (foo7, void(char(&)[2]), nil)
                   (foo8, void(short), nil)
                   (foo9, void(short(&)[2]), nil)
                   (foo10, void(int), nil)
                   (foo11, void(int(&)[2]), nil)
                   (foo12, void(long), nil)
                   (foo13, void(long(&)[2]), nil)
                   (foo14, void(float), nil)
                   (foo15, void(float(&)[2]), nil)
                   (foo16, void(double), nil)
                   (foo17, void(double(&)[2]), nil)
                  )
                  (constructors
                   (Signatures())
                  )
                )

void test(jvb::jvm jvm, jvb::environment e)
{
  Signatures sig(e);

  sig.foo1()(e);
  // bool
  sig.foo2()(e, true);
  jvb::array<bool> boolean_array;
  sig.foo3()(e, boolean_array);
  //byte
  jvb::byte byte = 15;
  sig.foo4()(e, byte);
  jvb::array<jvb::byte> byte_array;
  sig.foo5()(e, byte_array);
  //char
  jvb::char_ char_ = 15;
  sig.foo6()(e, char_);
  jvb::array<jvb::char_> char_array;
  sig.foo7()(e, char_array);
  //short
  jvb::short_ short_ = 15;
  sig.foo8()(e, short_);
  jvb::array<jvb::short_> short_array;
  sig.foo9()(e, short_array);
  //int
  jvb::int_ int_ = 15;
  sig.foo10()(e, int_);
  jvb::array<jvb::int_> int_array;
  sig.foo11()(e, int_array);
  //long
  jvb::long_ long_ = 15;
  sig.foo12()(e, long_);
  jvb::array<jvb::long_> long_array;
  sig.foo13()(e, long_array);
  //float
  jvb::float_ float_ = 15.0f;
  sig.foo14()(e, float_);
  jvb::array<jvb::float_> float_array;
  sig.foo15()(e, float_array);
  //double
  jvb::double_ double_ = 15.0;
  sig.foo16()(e, double_);
  jvb::array<jvb::double_> double_array;
  sig.foo17()(e, double_array);
}

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
  const std::size_t number_of_names = 1;
  const char* names[number_of_names]
    = {
       "jvb/tests/Signatures"
      };
  if(argc != number_of_names+1)
  {
    std::cout << "Must be passed 3 classes files compiled for tests" << std::endl;
    std::abort();
  }

  jvb::jvm jvm;
  jvb::environment e = jvm.environment();

  for(std::size_t i = 0; i != number_of_names; ++i)
  {
    std::cout << "loading " << argv[i+1] << " with " << names[i] << std::endl;
    e.load_class(argv[i+1], names[i]);
  }

  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&test, jvm, e) ));

  return 0;
}
