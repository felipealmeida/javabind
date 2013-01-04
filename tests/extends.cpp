// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

JVB_ADAPT_CLASS((jvb)(tests)(ExtendsBase)
                , (public)
                , (methods
                   (foo, void(), nil)
                   (bar, void(), nil)
                  )
                  (constructors
                   (ExtendsBase())
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(Extends)
                , (public)
                , (extends ExtendsBase)
                  (methods
                   (bar, void(), nil)
                  )
                  (constructors
                   (Extends())
                  )
                )

void test_inherited_members(jvb::jvm jvm, jvb::environment e)
{
  std::cout << "test_inherited_members" << std::endl;

  assert(e != jvb::environment());

  Extends extends(e);
  extends.foo()(e);
}

void test_virtual_members(jvb::jvm jvm, jvb::environment e)
{
  std::cout << "test_virtual_members" << std::endl;

  assert(e != jvb::environment());

  Extends extends(e);
  ExtendsBase base = extends;
  base.bar()(e);
}

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
  const std::size_t number_of_names = 2;
  const char* names[number_of_names]
    = {
       "jvb/tests/Extends"
       , "jvb/tests/ExtendsBase"
      };

  if(argc != number_of_names + 1)
  {
    std::cout << "Must be passed " << number_of_names << " classes files compiled for tests" << std::endl;
    std::abort();
  }

  jvb::jvm jvm;
  jvb::environment e = jvm.environment();

  for(int i = 1; i != -1; --i)
  {
    std::cout << "loading " << argv[i+1] << " with " << names[i] << std::endl;
    e.load_class(argv[i+1], names[i]);
  }

  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&test_inherited_members, jvm, e) ));

  return 0;
}

