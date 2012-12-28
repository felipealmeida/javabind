// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JCL_JAVA_IO_FILTEROUTPUTSTREAM_HPP
#define JVB_JCL_JAVA_IO_FILTEROUTPUTSTREAM_HPP

#include <jvb/adapt_class.hpp>
#include <jvb/array.hpp>
#include <jvb/primitives.hpp>

namespace jvb { namespace jcl { namespace java { namespace io {

JVB_ADAPT_CLASS((java)(io)(FilterOutputStream)
                , public
                , (methods
                   (close, void(), nil)
                   (flush, void(), nil)
                  )
                  (overloads
                   (write,
                    (void(jvb::array<jvb::byte>))
                    (void(jvb::array<jvb::byte>, jvb::int_, jvb::int_))
                    (void(jvb::int_)))
                  )
                )

} } } }

#endif
