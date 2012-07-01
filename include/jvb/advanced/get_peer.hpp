// (c) Copyright 2010-2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_ADVANCED_GET_PEER_HPP
#define JAVABIND_ADVANCED_GET_PEER_HPP

#include <javabind/env.hpp>
#include <javabind/object.hpp>
#include <javabind/class.hpp>
#include <javabind/detail/peer_info.hpp>

namespace javabind {

template <typename T>
T& get_peer(object obj, const char* class_name)
{
  javabind::class_ class_ = env(obj.environment()).find_class(class_name);
  field<long_> peer_field = class_.find_field<long_>("peer");
  long_ peer = peer_field.get(obj);
  assert(peer != 0);
  detail::peer_info<T>* info = reinterpret_cast<detail::peer_info<T>*>(peer.raw());
  return info->self;
}

template <typename T>
T& get_peer(object obj)
{
  field<long_> peer_field = obj.class_().find_field<long_>("peer");
  long_ peer = peer_field.get(obj);
  assert(peer != 0);
  detail::peer_info<T>* info = reinterpret_cast<detail::peer_info<T>*>(peer.raw());
  return info->self;
}

template <typename T>
T& get_peer(JNIEnv* env, jobject obj)
{
  return get_peer<T>(object(obj, env));
}

}

#endif
