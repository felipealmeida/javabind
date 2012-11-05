// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_IO_PRINTSTREAM_HPP
#define JVB_JCL_JAVA_IO_PRINTSTREAM_HPP

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
                , (methods (println, void(jvb::string))))

inline bool operator==(PrintStream const& lhs, PrintStream const& rhs)
{
  return true;
}

// struct PrintStream_class : extends<PrintStream_class, Class>
// {
//   PrintStream_class(environment e, const char* name = "java/io/PrintStream")
//     : base_type(e, name)
//   {}
// };

// struct PrintStream : Object
// {
//   typedef PrintStream_class class_type;

//   PrintStream()
//   {
//     std::cout << "PrintStream::PrintStream default" << std::endl;
//   }
//   explicit PrintStream(environment e, jobject obj)
//     : Object(obj), println(e, raw(), "println")
//   {
//     std::cout << "PrintStream::PrintStream" << std::endl;
//     assert(obj != 0);
//   }

//   method<void(jvb::string)> println;
// };

} } } }

#endif
