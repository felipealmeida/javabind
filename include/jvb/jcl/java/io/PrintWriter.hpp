// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_IO_PRINTWRITER_HPP
#define JVB_JCL_JAVA_IO_PRINTWRITER_HPP

#include <jvb/adapt_class.hpp>

#include <jvb/jcl/java/io/Writer.hpp>

namespace jvb { namespace jcl { namespace java { namespace io {

// JVB_ADAPT_CLASS((java)(io)(PrintWriter)
//                 , public
//                 , (methods 
//                    (checError, bool(), nil)
//                    (close, void(), nil)
//                    (flush, void(), nil)
//                    (setError, void(), nil)
//                    // (append, PrintWriter(char_))
//                   )
//                   // (overloads
//                   //  // (append
//                   //  //  (PrintWriter(char_))
//                   //  //  (PrintWriter(CharSequence))
//                   //  //  (PrintWriter(CharSequence, int_, int_))
//                   //  // ) // append
//                   //  // (format
//                   //  //  (PrintWriter (Locale, string, Object...))
//                   //  //  (PrintWriter (string, Object...))
//                   //  // ) // format
//                   //  (print,
//                   //   (void(bool))
//                   //   (void(char_))
//                   //   (void(array<char_))
//                   //   (void(double_))
//                   //   (void(float_))
//                   //   (void(int_))
//                   //   (void(long_))
//                   //   // (void(Object))
//                   //   // (void(String))
//                   //  )
//                    // (printf
//                    //  (PrintWriter(Locale, String, Object ...))
//                    //  (PrintWriter(String, Object ...))
//                    // ) // printf
//                    // (println,
//                    //  (void())
//                    //  (void(bool))
//                    //  (void(char_))
//                    //  (void(array<char_>))
//                    //  (void(double_))
//                    //  (void(float_))
//                    //  (void(int_))
//                    //  (void(long_))
//                    //  // (void(Object))
//                    //  // (void(String))
//                    // ) // println
//                    // (write,
//                    //  (void(array<char_>))
//                    //  (void(array<char_>, int_, int_))
//                    //  (void(int_))
//                    //  // (void(String))
//                    //  // (void(String, int_, int_))
//                    // ) // write
//                   // ) // overloads
//                   // (attributes
//                   //  (out, Writer, nil)
//                   // )
//                   (constructors
//                    // (PrintWriter(File))
//                    // (PrintWriter(File, String))
//                    // (PrintWriter(OutputStream))
//                    // (PrintWriter(OutputStream, bool))
//                    (PrintWriter(String))
//                    (PrintWriter(String, String))
//                    (PrintWriter(Writer))
//                    (PrintWriter(Writer, bool))
//                   ) // constructors
//                 )

} } } }

#endif
