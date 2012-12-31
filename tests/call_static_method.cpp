// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodVoid)
                , (public)
                , (methods
                   (method, void(), static)
                  )
                  (constructors
                   (CallStaticMethodVoid())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodBoolean)
                , (public)
                , (methods
                   (method, bool(), static)
                  )
                  (constructors
                   (CallStaticMethodBoolean())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayBoolean)
                , (public)
                , (methods
                   (method, jvb::array<bool>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayBoolean())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodByte)
                , (public)
                , (methods
                   (method, jvb::byte(), static)
                  )
                  (constructors
                   (CallStaticMethodByte())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayByte)
                , (public)
                , (methods
                   (method, jvb::array<jvb::byte>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayByte())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodChar)
                , (public)
                , (methods
                   (method, jvb::char_(), static)
                  )
                  (constructors
                   (CallStaticMethodChar())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayChar)
                , (public)
                , (methods
                   (method, jvb::array<jvb::char_>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayChar())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodShort)
                , (public)
                , (methods
                   (method, jvb::short_(), static)
                  )
                  (constructors
                   (CallStaticMethodShort())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayShort)
                , (public)
                , (methods
                   (method, jvb::array<jvb::short_>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayShort())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodInt)
                , (public)
                , (methods
                   (method, jvb::int_(), static)
                  )
                  (constructors
                   (CallStaticMethodInt())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayInt)
                , (public)
                , (methods
                   (method, jvb::array<jvb::int_>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayInt())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodLong)
                , (public)
                , (methods
                   (method, jvb::long_(), static)
                  )
                  (constructors
                   (CallStaticMethodLong())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayLong)
                , (public)
                , (methods
                   (method, jvb::array<jvb::long_>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayLong())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodFloat)
                , (public)
                , (methods
                   (method, jvb::float_(), static)
                  )
                  (constructors
                   (CallStaticMethodFloat())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayFloat)
                , (public)
                , (methods
                   (method, jvb::array<jvb::float_>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayFloat())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodDouble)
                , (public)
                , (methods
                   (method, jvb::double_(), static)
                  )
                  (constructors
                   (CallStaticMethodDouble())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayDouble)
                , (public)
                , (methods
                   (method, jvb::array<jvb::double_>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayDouble())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodObject)
                , (public)
                , (methods
                   (method, CallStaticMethodVoid(), static)
                  )
                  (constructors
                   (CallStaticMethodObject())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallStaticMethodArrayObject)
                , (public)
                , (methods
                   (method, jvb::array<CallStaticMethodVoid>(), static)
                  )
                  (constructors
                   (CallStaticMethodArrayObject())
                  )
                )

void call_method_void(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    CallStaticMethodVoid::method(e)(e);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_boolean(jvb::jvm jvm, jvb::environment e)
{
  assert(e != jvb::environment());
  try
  {
    bool v = CallStaticMethodBoolean::method(e)(e);
    assert(v == true);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_boolean(jvb::jvm jvm, jvb::environment e)
{
  assert(e != jvb::environment());
  try
  {
    jvb::array<bool> v = CallStaticMethodArrayBoolean::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<bool>::region_type region = v.all(e);
    assert(region[0] == true);
    assert(region[1] == false);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_byte(jvb::jvm jvm, jvb::environment e)
{
  assert(e != jvb::environment());
  try
  {
    jvb::byte v = CallStaticMethodByte::method(e)(e);
    assert(v == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_byte(jvb::jvm jvm, jvb::environment e)
{
  assert(e != jvb::environment());
  try
  {
    jvb::array<jvb::byte> v = CallStaticMethodArrayByte::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<jvb::byte>::region_type region = v.all(e);
    assert(region[0] == 15);
    assert(region[1] == 16);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_char(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::char_ v = CallStaticMethodChar::method(e)(e);
    std::cout << "call_method_char value " << (int)v.raw() << std::endl;
    assert(v == 'a');
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_char(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::char_> v = CallStaticMethodArrayChar::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<jvb::char_>::region_type region = v.all(e);
    assert(region[0] == 'a');
    assert(region[1] == 'b');
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_short(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::short_ v = CallStaticMethodShort::method(e)(e);
    std::cout << "call_method_short value " << (int)v.raw() << std::endl;
    assert(v == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_short(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::short_> v = CallStaticMethodArrayShort::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<jvb::short_>::region_type region = v.all(e);
    assert(region[0] == 15);
    assert(region[1] == 16);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::int_ v = CallStaticMethodInt::method(e)(e);
    std::cout << "call_method_int value " << v.raw() << std::endl;
    assert(v == 15.0f);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::int_> v = CallStaticMethodArrayInt::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<jvb::int_>::region_type region = v.all(e);
    assert(region[0] == 15);
    assert(region[1] == 16);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_long(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::long_ v = CallStaticMethodLong::method(e)(e);
    std::cout << "call_method_long value " << v.raw() << std::endl;
    assert(v == 15.0f);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_long(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::long_> v = CallStaticMethodArrayLong::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<jvb::long_>::region_type region = v.all(e);
    assert(region[0] == 15);
    assert(region[1] == 16);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_float(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::float_ v = CallStaticMethodFloat::method(e)(e);
    std::cout << "call_method_float value " << v.raw() << std::endl;
    assert(v == 15.0f);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_float(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::float_> v = CallStaticMethodArrayFloat::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<jvb::float_>::region_type region = v.all(e);
    assert(region[0] == 15.0f);
    assert(region[1] == 16.0f);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_double(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::double_ v = CallStaticMethodDouble::method(e)(e);
    std::cout << "call_method_double value " << v.raw() << std::endl;
    assert(v == 15.0);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_double(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::double_> v = CallStaticMethodArrayDouble::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<jvb::double_>::region_type region = v.all(e);
    assert(region[0] == 15.0);
    assert(region[1] == 16.0);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_object(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    CallStaticMethodVoid v = CallStaticMethodObject::method(e)(e);
    v.method(e)(e);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void call_method_array_object(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<CallStaticMethodVoid> v = CallStaticMethodArrayObject::method(e)(e);
    assert(v.length(e) == 2);
    jvb::array<CallStaticMethodVoid>::region_type region = v.all(e);
    region[0].method(e)(e);
    assert(!region[1]);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
  const std::size_t number_of_names = 19;
  const char* names[number_of_names]
    = {
       "jvb/tests/CallStaticMethodArrayBoolean"
       , "jvb/tests/CallStaticMethodArrayByte"
       , "jvb/tests/CallStaticMethodArrayChar"
       , "jvb/tests/CallStaticMethodArrayDouble"
       , "jvb/tests/CallStaticMethodArrayFloat"
       , "jvb/tests/CallStaticMethodArrayInt"
       , "jvb/tests/CallStaticMethodArrayLong"
       , "jvb/tests/CallStaticMethodArrayObject"
       , "jvb/tests/CallStaticMethodArrayShort"
       , "jvb/tests/CallStaticMethodBoolean"
       , "jvb/tests/CallStaticMethodByte"
       , "jvb/tests/CallStaticMethodChar"
       , "jvb/tests/CallStaticMethodDouble"
       , "jvb/tests/CallStaticMethodFloat"
       , "jvb/tests/CallStaticMethodInt"
       , "jvb/tests/CallStaticMethodLong"
       , "jvb/tests/CallStaticMethodObject"
       , "jvb/tests/CallStaticMethodShort"
       , "jvb/tests/CallStaticMethodVoid"
      };
  if(argc != number_of_names + 1)
  {
    std::cout << "Must be passed " << number_of_names << " classes files compiled for tests" << std::endl;
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
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_boolean, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_byte, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_char, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_double, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_float, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_int, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_long, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_object, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_array_short, jvm, e) ));

  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_boolean, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_byte, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_char, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_double, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_float, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_int, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_long, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_object, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_short, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&call_method_void, jvm, e) ));

  return 0;
}
