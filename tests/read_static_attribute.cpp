// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeByte)
                , (public)
                , (attributes
                   (attribute, jvb::byte, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeChar)
                , (public)
                , (attributes
                   (attribute, jvb::char_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeShort)
                , (public)
                , (attributes
                   (attribute, jvb::short_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeInt)
                , (public)
                , (attributes
                   (attribute, jvb::int_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeLong)
                , (public)
                , (attributes
                   (attribute, jvb::long_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeFloat)
                , (public)
                , (attributes
                   (attribute, jvb::float_, static)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticAttributeDouble)
                , (public)
                , (attributes
                   (attribute, jvb::double_, static)
                  )
                )

void read_static_attribute_byte(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadStaticAttributeByte");
    assert(ReadStaticAttributeByte::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_char(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadStaticAttributeChar");
    assert(ReadStaticAttributeChar::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_short(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadStaticAttributeShort");
    assert(ReadStaticAttributeShort::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_int(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadStaticAttributeInt");
    assert(ReadStaticAttributeInt::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_long(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadStaticAttributeLong");
    assert(ReadStaticAttributeLong::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_float(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadStaticAttributeFloat");
    assert(ReadStaticAttributeFloat::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_static_attribute_double(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadStaticAttributeDouble");
    assert(ReadStaticAttributeDouble::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
  if(argc != 8)
  {
    std::cout << "Must be passed 3 classes files compiled for tests" << std::endl;
    std::abort();
  }

  jvb::jvm jvm;

  int i = 1;
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_byte, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_char, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_double, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_float, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_int, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_long, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_static_attribute_short, jvm, argv[i++]) ));

  return 0;
}
