// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeBoolean)
                , (public)
                , (attributes
                   (attribute, bool, nil)
                  )
                  (constructors
                   (ReadAttributeBoolean())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayBoolean)
                , (public)
                , (attributes
                   (attribute, jvb::array<bool>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayBoolean())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeByte)
                , (public)
                , (attributes
                   (attribute, jvb::byte, nil)
                  )
                  (constructors
                   (ReadAttributeByte())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeChar)
                , (public)
                , (attributes
                   (attribute, jvb::char_, nil)
                  )
                  (constructors
                   (ReadAttributeChar())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeShort)
                , (public)
                , (attributes
                   (attribute, jvb::short_, nil)
                  )
                  (constructors
                   (ReadAttributeShort())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeInt)
                , (public)
                , (attributes
                   (attribute, jvb::int_, nil)
                  )
                  (constructors
                   (ReadAttributeInt())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeLong)
                , (public)
                , (attributes
                   (attribute, jvb::long_, nil)
                  )
                  (constructors
                   (ReadAttributeLong())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeFloat)
                , (public)
                , (attributes
                   (attribute, jvb::float_, nil)
                  )
                  (constructors
                   (ReadAttributeFloat())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeDouble)
                , (public)
                , (attributes
                   (attribute, jvb::double_, nil)
                  )
                  (constructors
                   (ReadAttributeDouble())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeObject)
                , (public)
                , (attributes
                   (attribute, ReadAttributeByte, nil)
                  )
                  (constructors
                   (ReadAttributeObject())
                  )
                )

void read_attribute_boolean(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeBoolean");
    ReadAttributeBoolean object(e);
    assert(object.attribute(e)() == true);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_byte(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeByte");
    ReadAttributeByte object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_char(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeChar");
    ReadAttributeChar object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_short(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeShort");
    ReadAttributeShort object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_int(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeInt");
    ReadAttributeInt object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_long(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeLong");
    ReadAttributeLong object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_float(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeFloat");
    ReadAttributeFloat object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_double(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeDouble");
    ReadAttributeDouble object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_object(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/ReadAttributeObject");
    ReadAttributeObject object(e);
    ReadAttributeByte obj = object.attribute(e)();
    static_cast<void>(obj);
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
      };
  if(argc != 10)
  {
    std::cout << "Must be passed 3 classes files compiled for tests" << std::endl;
    std::abort();
  }

  jvb::jvm jvm;

  int i = 1;
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_boolean, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_byte, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_char, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_double, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_float, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_int, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_long, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_object, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_short, jvm, argv[i++]) ));

  return 0;
}
