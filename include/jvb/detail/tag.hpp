// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_TAG_HPP
#define JVB_DETAIL_TAG_HPP

namespace jvb { namespace detail {

template <typename Tag>
struct tag
{
  typedef Tag type;
};

} }

#endif
