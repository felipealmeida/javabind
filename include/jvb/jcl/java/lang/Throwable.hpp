// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_LANG_THROWABLE_HPP
#define JVB_JCL_JAVA_LANG_THROWABLE_HPP

#include <jvb/jcl/java/io/PrintStream.hpp>
#include <jvb/jcl/java/io/PrintWriter.hpp>

#include <jvb/adapt_class.hpp>
#include <jvb/string.hpp>

namespace jvb { namespace jcl { namespace java { namespace lang {

JVB_ADAPT_CLASS((java)(lang)(Throwable)
                , (public)
                , (constructors
                   (Throwable())
                   (Throwable(String))
                   (Throwable(String, Throwable))
                  )
                  (methods
                   (fillInStackTrace, Throwable(), nil)
                   (getCause, Throwable(), nil)
                   (getLocalizedMessage, String(), nil)
                   (getMessage, String(), nil)
                   // (getStackTrace, jvb::array<StackTraceElement>(), nil)
                   (initCause, Throwable(Throwable), nil)
                   // (setStackTrace, void(jvb::array<StackTraceElement>), nil)
                   (toString, String(), nil)
                  )
                  (overloads
                   (printStackTrace,
                    (void())
                    (void(io::PrintStream))
                    (void(io::PrintWriter))
                   )
                  )
                )

} } } }

#endif
