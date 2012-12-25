// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>

#include <jni.h>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(ReadStaticIntAttribute)
                , (public)
                , (attributes
                   (attribute, jvb::int_, static)
                  )
                )

int main(int argc, char* argv[])
{
  assert(argc == 2);
  jvb::jvm jvm(jvb::keywords::_interpreted_only = true);
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(argv[1], "jvb/tests/ReadStaticIntAttribute");
    assert(ReadStaticIntAttribute::attribute(e)() == 15);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}
