// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

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
