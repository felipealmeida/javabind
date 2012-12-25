// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_LANG_SYSTEM_HPP
#define JVB_JCL_JAVA_LANG_SYSTEM_HPP

#include <jvb/jcl/java/io/PrintStream.hpp>
#include <jvb/environment.hpp>
#include <jvb/class.hpp>
#include <jvb/object.hpp>
#include <jvb/static_field.hpp>
#include <jvb/adapt_class.hpp>

namespace jvb { namespace jcl { namespace java { namespace lang {

JVB_ADAPT_CLASS((java)(lang)(System)
                , public
                , (attributes (out, io::PrintStream, static)))

} } } }

#endif
