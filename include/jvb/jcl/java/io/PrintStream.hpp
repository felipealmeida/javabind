// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_IO_PRINTSTREAM_HPP
#define JVB_JCL_JAVA_IO_PRINTSTREAM_HPP

#include <jvb/jcl/java/io/FilterOutputStream.hpp>
#include <jvb/environment.hpp>
#include <jvb/class.hpp>
#include <jvb/object.hpp>
#include <jvb/field.hpp>
#include <jvb/method.hpp>
#include <jvb/string.hpp>
#include <jvb/adapt_class.hpp>

namespace jvb { namespace jcl { namespace java { namespace io {

JVB_ADAPT_CLASS((java)(io)(PrintStream)
                , public
                , (overloads
                   (println,
                    (void())
                    (void(bool))
                    (void(char_))
                    (void(array<char_>))
                    (void(double_))
                    (void(float_))
                    (void(int_))
                    (void(long_))
                    (void(Object))
                    (void(String))
                   ) // println
                  ) // overloads
                )

} } } }

#endif
