// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_PEER_INFO_HPP
#define JAVABIND_DETAIL_PEER_INFO_HPP

#include <javabind/detail/bootstrap_info.hpp>
#include <javabind/reg/constructor.hpp>
#include <javabind/reg/extends.hpp>

namespace javabind { namespace detail {

template <typename T>
struct peer_info
{
  detail::bootstrap_info* bootstrap_info;

  peer_info(detail::bootstrap_info* bootstrap_info, reg::default_constructor_tag)
    : bootstrap_info(bootstrap_info) {}

  peer_info(detail::bootstrap_info* bootstrap_info, reg::default_constructor_tag
            , reg::extends_adl_protect::extends_info info)
    : bootstrap_info(bootstrap_info), self(info) {}

  template <typename F>
  peer_info(detail::bootstrap_info* bootstrap_info, F f)
    : bootstrap_info(bootstrap_info), self(f()) {}

  template <typename F>
  peer_info(detail::bootstrap_info* bootstrap_info, F f
            , reg::extends_adl_protect::extends_info info)
    : bootstrap_info(bootstrap_info), self(f(info)) {}
  
  T self;
};

} }

#endif
