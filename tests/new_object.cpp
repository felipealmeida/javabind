// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>

#include <jni.h>

#include <cstdlib>

JVB_ADAPT_CLASS((jvb)(tests)(NewObject)
                , (public)
                , (constructors
                   (NewObject())
                  )
                )

int main(int argc, char* argv[])
{
  jvb::jvm jvm;
  jvb::environment e = jvm.environment();

  try
  {
    e.load_class(argv[1], "jvb/tests/NewObject");
    NewObject object(e);
  }
  catch(jvb::thrown_error const& ex)
  {
    std::cout << ostream_wrap(e, ex.exception()) << std::endl;
    throw;
  }
}
