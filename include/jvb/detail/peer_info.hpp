// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_DETAIL_PEER_INFO_HPP
#define JAVABIND_DETAIL_PEER_INFO_HPP

#include <javabind/detail/bootstrap_info.hpp>
#include <javabind/reg/constructor.hpp>
#include <javabind/reg/extends.hpp>
#include <javabind/reg/object.hpp>

namespace javabind { namespace detail {

template <typename T>
struct peer_info
{
  detail::bootstrap_info* bootstrap_info;

  peer_info(detail::bootstrap_info* bootstrap_info, reg::default_constructor_tag
            , JNIEnv* env, reg::object_info oinfo)
    : bootstrap_info(bootstrap_info), self(env, oinfo) {}

  peer_info(detail::bootstrap_info* bootstrap_info, reg::default_constructor_tag
            , JNIEnv* env, reg::object_info oinfo, reg::extends_info info)
    : bootstrap_info(bootstrap_info), self(env, oinfo, info) {}

  template <typename F>
  peer_info(detail::bootstrap_info* bootstrap_info, F f
            , JNIEnv* env, reg::object_info oinfo)
    : bootstrap_info(bootstrap_info), self(f(env, oinfo)) {}

  template <typename F>
  peer_info(detail::bootstrap_info* bootstrap_info, F f
            , JNIEnv* env, reg::object_info oinfo, reg::extends_info info)
    : bootstrap_info(bootstrap_info), self(f(env, oinfo, info)) {}
  
  T self;
};

} }

#endif
