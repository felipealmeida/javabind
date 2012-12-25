// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE create_jvm
#include <boost/test/included/unit_test.hpp>

#include <jvb/jvb.hpp>

BOOST_AUTO_TEST_CASE (create_jvm)
{
  jvb::jvm jvm;
}
