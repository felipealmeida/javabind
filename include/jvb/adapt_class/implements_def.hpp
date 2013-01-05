// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_CLASS_IMPLEMENTS_DEF_HPP
#define JVB_ADAPT_CLASS_IMPLEMENTS_DEF_HPP

#include <jvb/detail/hidden_object.hpp>

#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/seq/filter.hpp>

#define JVB_ADAPT_CLASS_IMPLEMENTS_DEF(INTERFACE)                       \
  operator INTERFACE () const                                           \
  {                                                                     \
    return INTERFACE( ::jvb::detail::hidden_object(raw()) );       \
  }

#endif

