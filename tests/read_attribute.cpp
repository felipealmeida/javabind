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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayByte)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::byte>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayByte())
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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayChar)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::char_>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayChar())
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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayShort)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::short_>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayShort())
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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayInt)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::int_>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayInt())
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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayLong)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::long_>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayLong())
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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayFloat)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::float_>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayFloat())
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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayDouble)
                , (public)
                , (attributes
                   (attribute, jvb::array<jvb::double_>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayDouble())
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

JVB_ADAPT_CLASS((jvb)(tests)(ReadAttributeArrayObject)
                , (public)
                , (attributes
                   (attribute, jvb::array<ReadAttributeByte>, nil)
                  )
                  (constructors
                   (ReadAttributeArrayObject())
                  )
                )

void read_attribute_boolean(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeBoolean object(e);
    assert(object.attribute(e)() == true);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_boolean(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayBoolean object(e);
    jvb::array<bool>  v = object.attribute(e)();
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

void read_attribute_byte(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeByte object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_byte(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayByte object(e);
    jvb::array<jvb::byte>  v = object.attribute(e)();
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

void read_attribute_char(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeChar object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_char(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayChar object(e);
    jvb::array<jvb::char_>  v = object.attribute(e)();
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

void read_attribute_short(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeShort object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_short(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayShort object(e);
    jvb::array<jvb::short_> v = object.attribute(e)();
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

void read_attribute_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeInt object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_int(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayInt object(e);
    jvb::array<jvb::int_> v = object.attribute(e)();
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

void read_attribute_long(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeLong object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_long(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayLong object(e);
    jvb::array<jvb::long_> v = object.attribute(e)();
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

void read_attribute_float(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeFloat object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_float(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayFloat object(e);
    jvb::array<jvb::float_> v = object.attribute(e)();
    assert(v.length(e) == 2);
    jvb::array<jvb::float_>::region_type region = v.all(e);
    assert(region[0] == 15.0);
    assert(region[1] == 16.0);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_double(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeDouble object(e);
    assert(object.attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void read_attribute_array_double(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayDouble object(e);
    jvb::array<jvb::double_> v = object.attribute(e)();
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

void read_attribute_object(jvb::jvm jvm, jvb::environment e)
{
  try
  {
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

void read_attribute_array_object(jvb::jvm jvm, jvb::environment e)
{
  try
  {
    ReadAttributeArrayObject object(e);
    jvb::array<ReadAttributeByte> v = object.attribute(e)();
    assert(v.length(e) == 2);
    jvb::array<ReadAttributeByte>::region_type region = v.all(e);
    assert(region[0].attribute(e)() == 'a');
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
       "jvb/tests/ReadAttributeArrayBoolean"
       , "jvb/tests/ReadAttributeArrayByte"
       , "jvb/tests/ReadAttributeArrayChar"
       , "jvb/tests/ReadAttributeArrayDouble"
       , "jvb/tests/ReadAttributeArrayFloat"
       , "jvb/tests/ReadAttributeArrayInt"
       , "jvb/tests/ReadAttributeArrayLong"
       , "jvb/tests/ReadAttributeArrayObject"
       , "jvb/tests/ReadAttributeArrayShort"
       , "jvb/tests/ReadAttributeBoolean"
       , "jvb/tests/ReadAttributeByte"
       , "jvb/tests/ReadAttributeChar"
       , "jvb/tests/ReadAttributeDouble"
       , "jvb/tests/ReadAttributeFloat"
       , "jvb/tests/ReadAttributeInt"
       , "jvb/tests/ReadAttributeLong"
       , "jvb/tests/ReadAttributeObject"
       , "jvb/tests/ReadAttributeShort"
      };
  if(argc != number_of_names+1)
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
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_array_boolean, jvm, e) ));

  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_boolean, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_byte, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_char, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_double, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_float, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_int, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_long, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_object, jvm, e) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&read_attribute_short, jvm, e) ));

  return 0;
}
