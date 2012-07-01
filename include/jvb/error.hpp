// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ERROR_HPP
#define JVB_ERROR_HPP

#include <jvb/jvb_error.hpp>

namespace jvb { namespace error {



} }

#ifndef JVB_DISABLE_BOOST_EXCEPTION
#define JVB_THROW_EXCEPTION(x) BOOST_THROW_EXCEPTION(x)
#else
#define JVB_THROW_EXCEPTION(x) throw x
#endif

#endif

