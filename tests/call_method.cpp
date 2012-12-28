// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodVoid)
                , (public)
                , (methods
                   (method, void(), nil)
                  )
                  (constructors
                   (CallMethodVoid())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodBoolean)
                , (public)
                , (methods
                   (method, bool(), nil)
                  )
                  (constructors
                   (CallMethodBoolean())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayBoolean)
                , (public)
                , (methods
                   (method, jvb::array<bool>(), nil)
                  )
                  (constructors
                   (CallMethodBoolean())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodByte)
                , (public)
                , (methods
                   (method, jvb::byte(), nil)
                  )
                  (constructors
                   (CallMethodByte())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayByte)
                , (public)
                , (methods
                   (method, jvb::array<jvb::byte>(), nil)
                  )
                  (constructors
                   (CallMethodByte())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodChar)
                , (public)
                , (methods
                   (method, jvb::char_(), nil)
                  )
                  (constructors
                   (CallMethodChar())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayChar)
                , (public)
                , (methods
                   (method, jvb::array<jvb::char_>(), nil)
                  )
                  (constructors
                   (CallMethodChar())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodShort)
                , (public)
                , (methods
                   (method, jvb::short_(), nil)
                  )
                  (constructors
                   (CallMethodShort())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayShort)
                , (public)
                , (methods
                   (method, jvb::array<jvb::short_>(), nil)
                  )
                  (constructors
                   (CallMethodArrayShort())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodInt)
                , (public)
                , (methods
                   (method, jvb::int_(), nil)
                  )
                  (constructors
                   (CallMethodInt())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayInt)
                , (public)
                , (methods
                   (method, jvb::array<jvb::int_>(), nil)
                  )
                  (constructors
                   (CallMethodArrayInt())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodLong)
                , (public)
                , (methods
                   (method, jvb::long_(), nil)
                  )
                  (constructors
                   (CallMethodLong())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayLong)
                , (public)
                , (methods
                   (method, jvb::array<jvb::long_>(), nil)
                  )
                  (constructors
                   (CallMethodArrayLong())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodFloat)
                , (public)
                , (methods
                   (method, jvb::float_(), nil)
                  )
                  (constructors
                   (CallMethodFloat())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayFloat)
                , (public)
                , (methods
                   (method, jvb::array<jvb::float_>(), nil)
                  )
                  (constructors
                   (CallMethodArrayFloat())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodDouble)
                , (public)
                , (methods
                   (method, jvb::double_(), nil)
                  )
                  (constructors
                   (CallMethodDouble())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayDouble)
                , (public)
                , (methods
                   (method, jvb::array<jvb::double_>(), nil)
                  )
                  (constructors
                   (CallMethodArrayDouble())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodObject)
                , (public)
                , (methods
                   (method, CallMethodVoid(), nil)
                  )
                  (constructors
                   (CallMethodObject())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(CallMethodArrayObject)
                , (public)
                , (methods
                   (method, jvb::array<CallMethodVoid>(), nil)
                  )
                  (constructors
                   (CallMethodArrayObject())
                  )
                )

void call_method_void(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    CallMethodVoid object(e);
    object.method()(e);
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
    CallMethodBoolean object(e);
    bool v = object.method()(e);
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
    CallMethodArrayBoolean object(e);
    jvb::array<bool> v = object.method()(e);
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
    CallMethodByte object(e);
    jvb::byte v = object.method()(e);
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
    CallMethodArrayByte object(e);
    jvb::array<jvb::byte> v = object.method()(e);
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
    CallMethodChar object(e);
    jvb::char_ v = object.method()(e);
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
    CallMethodArrayChar object(e);
    jvb::array<jvb::char_> v = object.method()(e);
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
    CallMethodShort object(e);
    jvb::short_ v = object.method()(e);
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
    CallMethodArrayShort object(e);
    jvb::array<jvb::short_> v = object.method()(e);
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

void call_method_array_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    CallMethodArrayInt object(e);
    jvb::array<jvb::int_> v = object.method()(e);
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

void call_method_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    CallMethodInt object(e);
    jvb::int_ v = object.method()(e);
    std::cout << "call_method_int value " << v.raw() << std::endl;
    assert(v == 15.0f);
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
    CallMethodLong object(e);
    jvb::long_ v = object.method()(e);
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
    CallMethodArrayLong object(e);
    jvb::array<jvb::long_> v = object.method()(e);
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
    CallMethodFloat object(e);
    jvb::float_ v = object.method()(e);
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
    CallMethodArrayFloat object(e);
    jvb::array<jvb::float_> v = object.method()(e);
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
    CallMethodDouble object(e);
    jvb::double_ v = object.method()(e);
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
    CallMethodArrayDouble object(e);
    jvb::array<jvb::double_> v = object.method()(e);
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
    CallMethodObject object(e);
    CallMethodVoid v = object.method()(e);
    v.method()(e);
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
    CallMethodArrayObject object(e);
    jvb::array<CallMethodVoid> v = object.method()(e);
    assert(v.length(e) == 2);
    jvb::array<CallMethodVoid>::region_type region = v.all(e);
    region[0].method()(e);
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
       "jvb/tests/CallMethodArrayBoolean"
       , "jvb/tests/CallMethodArrayByte"
       , "jvb/tests/CallMethodArrayChar"
       , "jvb/tests/CallMethodArrayDouble"
       , "jvb/tests/CallMethodArrayFloat"
       , "jvb/tests/CallMethodArrayInt"
       , "jvb/tests/CallMethodArrayLong"
       , "jvb/tests/CallMethodArrayObject"
       , "jvb/tests/CallMethodArrayShort"
       , "jvb/tests/CallMethodBoolean"
       , "jvb/tests/CallMethodByte"
       , "jvb/tests/CallMethodChar"
       , "jvb/tests/CallMethodDouble"
       , "jvb/tests/CallMethodFloat"
       , "jvb/tests/CallMethodInt"
       , "jvb/tests/CallMethodLong"
       , "jvb/tests/CallMethodObject"
       , "jvb/tests/CallMethodShort"
       , "jvb/tests/CallMethodVoid"
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
