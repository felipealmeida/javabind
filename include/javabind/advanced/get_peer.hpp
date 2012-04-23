// (c) Copyright 2010-2012 Felipe Magno de Almeida
//
// All rights reserved

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
  javabind::class_ class_ = env(obj.env).find_class(class_name);
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
