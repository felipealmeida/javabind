// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(NewObject)
                , (public)
                , (constructors
                   (NewObject())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(NewObjectByte)
                , (public)
                , (constructors
                   (NewObjectByte(jvb::byte))
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(NewObjectChar)
                , (public)
                , (constructors
                   (NewObjectChar(jvb::char_))
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(NewObjectShort)
                , (public)
                , (constructors
                   (NewObjectShort(jvb::short_))
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(NewObjectInt)
                , (public)
                , (constructors
                   (NewObjectInt(jvb::int_))
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(NewObjectLong)
                , (public)
                , (constructors
                   (NewObjectLong(jvb::long_))
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(NewObjectFloat)
                , (public)
                , (constructors
                   (NewObjectLong(jvb::float_))
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(NewObjectDouble)
                , (public)
                , (constructors
                   (NewObjectLong(jvb::double_))
                  )
                )

void new_object(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObject");
    NewObject object(e);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void new_object_byte(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObjectByte");
    NewObjectByte object(e, 5);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void new_object_char(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObjectChar");
    NewObjectChar object(e, 5);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void new_object_short(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObjectShort");
    NewObjectShort object(e, 5);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void new_object_int(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObjectInt");
    NewObjectInt object(e, 5);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void new_object_long(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObjectLong");
    NewObjectLong object(e, 5);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void new_object_float(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObjectFloat");
    NewObjectFloat object(e, 5);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

void new_object_double(jvb::jvm jvm, std::string const& filename)
{
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(filename, "jvb/tests/NewObjectDouble");
    NewObjectDouble object(e, 5);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
  if(argc != 9)
  {
    std::cout << "Must be passed 3 classes files compiled for tests" << std::endl;
    std::abort();
  }

  jvb::jvm jvm;

  int i = 1;
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object_byte, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object_char, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object_double, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object_float, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object_int, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object_long, jvm, argv[i++]) ));
  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&new_object_short, jvm, argv[i++]) ));

  return 0;
}
