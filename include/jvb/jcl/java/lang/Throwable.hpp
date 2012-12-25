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
                   (fillInStackTrace, Throwable())
                   (getCause, Throwable())
                   (getLocalizedMessage, String())
                   (getMessage, String())
                   // (getStackTrace, jvb::array<StackTraceElement>())
                   (initCause, Throwable(Throwable))
                   // (setStackTrace, void(jvb::array<StackTraceElement>))
                   (toString, String())
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
