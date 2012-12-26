// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_LANG_CHARSEQUENCE_HPP
#define JVB_JCL_JAVA_LANG_CHARSEQUENCE_HPP

#include <jvb/adapt_class.hpp>

namespace jvb { namespace jcl { namespace java { namespace lang {

JVB_ADAPT_INTERFACE((java)(lang)(CharSequence)
                    , public
                    , (methods
                       (charAt, char_(int_))
                       (length, int_())
                       (subSequence, CharSequence(int_, int_))
                      )
                    )

} } } }

#endif
