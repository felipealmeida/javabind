// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeBoolean)
                , (public)
                , (attributes
                   (attribute, bool, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayBoolean)
                , (public)
                , (attributes
                   (attribute, jvb::array<bool>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeByte)
                , (public)
                , (attributes
                   (attribute, jvb::byte, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayByte)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::byte>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeChar)
                , (public)
                , (attributes
                   (attribute, jvb::char_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayChar)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::char_>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeShort)
                , (public)
                , (attributes
                   (attribute, jvb::short_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayShort)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::short_>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeInt)
                , (public)
                , (attributes
                   (attribute, jvb::int_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayInt)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::int_>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeLong)
                , (public)
                , (attributes
                   (attribute, jvb::long_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayLong)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::long_>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeFloat)
                , (public)
                , (attributes
                   (attribute, jvb::float_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayFloat)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::float_>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeDouble)
                , (public)
                , (attributes
                   (attribute, jvb::double_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayDouble)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::double_>, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeObject)
                , (public)
                , (attributes
                   (attribute, ReadStaticAttributeByte, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeArrayObject)
                , (public)
                , (attributes
                   (attribute, jvb::array<ReadStaticAttributeByte>, static)
                  )
                )

void read_static_attribute_boolean(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeBoolean::attribute(e)() == true);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_boolean(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<bool> v = ReadStaticAttributeArrayBoolean::attribute(e)();
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

void read_static_attribute_byte(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeByte::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_byte(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::byte> v = ReadStaticAttributeArrayByte::attribute(e)();
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

void read_static_attribute_char(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeChar::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_char(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::char_> v = ReadStaticAttributeArrayChar::attribute(e)();
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

void read_static_attribute_short(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeShort::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_short(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::short_> v = ReadStaticAttributeArrayShort::attribute(e)();
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

void read_static_attribute_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeInt::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::int_> v = ReadStaticAttributeArrayInt::attribute(e)();
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

void read_static_attribute_long(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeLong::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_long(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::long_> v = ReadStaticAttributeArrayLong::attribute(e)();
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

void read_static_attribute_float(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeFloat::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_float(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::float_> v = ReadStaticAttributeArrayFloat::attribute(e)();
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

void read_static_attribute_double(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    assert(ReadStaticAttributeDouble::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_double(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<jvb::double_> v = ReadStaticAttributeArrayDouble::attribute(e)();
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

void read_static_attribute_object(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadStaticAttributeByte object = ReadStaticAttributeObject::attribute(e)();
    static_cast<void>(object);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_array_object(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    jvb::array<ReadStaticAttributeByte> v = ReadStaticAttributeArrayObject::attribute(e)();
    assert(v.length(e) == 2);
    jvb::array<ReadStaticAttributeByte>::region_type region = v.all(e);
    assert(region[0].attribute(e)() == 15);
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
  const std::size_t number_of_names = 18;
  const char* names[number_of_names]
    = {
       "jvb/tests/ReadStaticAttributeArrayBoolean"
       , "jvb/tests/ReadStaticAttributeArrayByte"
       , "jvb/tests/ReadStaticAttributeArrayChar"
       , "jvb/tests/ReadStaticAttributeArrayDouble"
       , "jvb/tests/ReadStaticAttributeArrayFloat"
       , "jvb/tests/ReadStaticAttributeArrayInt"
       , "jvb/tests/ReadStaticAttributeArrayLong"
       , "jvb/tests/ReadStaticAttributeArrayObject"
       , "jvb/tests/ReadStaticAttributeArrayShort"
       , "jvb/tests/ReadStaticAttributeBoolean"
       , "jvb/tests/ReadStaticAttributeByte"
       , "jvb/tests/ReadStaticAttributeChar"
       , "jvb/tests/ReadStaticAttributeDouble"
       , "jvb/tests/ReadStaticAttributeFloat"
       , "jvb/tests/ReadStaticAttributeInt"
       , "jvb/tests/ReadStaticAttributeLong"
       , "jvb/tests/ReadStaticAttributeObject"
       , "jvb/tests/ReadStaticAttributeShort"
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
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_boolean, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_byte, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_char, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_double, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_float, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_int, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_long, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_object, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_array_short, jvm, e) ));

  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_boolean, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_byte, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_char, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_double, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_float, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_int, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_long, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_object, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_short, jvm, e) ));

  return 0;
}
