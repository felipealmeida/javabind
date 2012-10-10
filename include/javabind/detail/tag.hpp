// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_DETAIL_TAG_HPP
#define JAVABIND_DETAIL_TAG_HPP

namespace javabind { namespace detail {

template <typename Tag>
struct tag
{
  typedef Tag type;
};

} }

#endif
