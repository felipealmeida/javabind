// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_IO_WRITER_HPP
#define JVB_JCL_JAVA_IO_WRITER_HPP

#include <jvb/adapt_class.hpp>

// #include <jvb/jcl/java/lang/CharSequence.hpp>

namespace jvb { namespace jcl { namespace java { namespace io {

JVB_ADAPT_CLASS((java)(io)(Writer)
                , public
                , (methods
                   (close, void(), nil)
                   (flush, void(), nil)
                   (append, void(char_), nil)
                  ) // methods
                  (overloads
                   (write,
                    (void(array<char_>))
                    (void(array<char_>, int_, int_))
                    (void(int_))
                    (void(string))
                    (void(string, int_, int_))
                   ) // write
                  // (append,
                  //    (void(char_))
                  //    (void(CharSequence))
                  //    (void(CharSequence, int_, int_))
                  // ) // append
                  ) // overloads
                  // (implements
                  //  (jvb::jcl::java::io::Appendable)
                  //  (jvb::jcl::java::io::Closeable)
                  //  (jvb::jcl::java::io::Flushable)
                  // )
                )

} } } }

#endif
