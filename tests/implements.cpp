// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <jvb/jvb.hpp>

JVB_ADAPT_CLASS((jvb)(tests)(Interface1)
                , (public)(interface)
                , (methods
                   (foo, void(), nil)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(Interface2)
                , (public)(interface)
                , (methods
                   (bar, void(), nil)
                  )
                )

JVB_ADAPT_CLASS((jvb)(tests)(Implements)
                , (public)
                , (implements (Interface1)(Interface2))
                  (methods
                   (bar, void(), nil)
                  )
                  (attributes
                   (bar_called, bool, nil)
                   (foo_called, bool, nil)
                  )
                  (constructors
                   (Implements())
                  )
                )

void test_virtual_members(jvb::jvm jvm, jvb::environment e)
{
  std::cout << "test_virtual_members" << std::endl;

  assert(e != jvb::environment());

  Implements implements(e);

  assert(implements.bar_called(e)() == false);
  assert(implements.foo_called(e)() == false);

  Interface1 interface1 = implements;
  interface1.foo()(e);

  assert(implements.foo_called(e)() == true);

  Interface2 interface2 = implements;
  interface2.bar()(e);

  assert(implements.bar_called(e)() == true);
}

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
  const std::size_t number_of_names = 3;
  const char* names[number_of_names]
    = {
       "jvb/tests/Implements"
       , "jvb/tests/Interface1"
       , "jvb/tests/Interface2"
      };

  if(argc != number_of_names + 1)
  {
    std::cout << "Must be passed " << number_of_names << " classes files compiled for tests" << std::endl;
    std::abort();
  }

  jvb::jvm jvm;
  jvb::environment e = jvm.environment();

  for(int i = number_of_names-1; i != -1; --i)
  {
    std::cout << "loading " << argv[i+1] << " with " << names[i] << std::endl;
    e.load_class(argv[i+1], names[i]);
  }

  boost::unit_test::framework::master_test_suite()
    .add( BOOST_TEST_CASE( boost::bind(&test_virtual_members, jvm, e) ));

  return 0;
}

