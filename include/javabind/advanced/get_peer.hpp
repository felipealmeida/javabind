// (c) Copyright 2010-2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_ADVANCED_GET_PEER_HPP
#define JAVABIND_ADVANCED_GET_PEER_HPP

#include <javabind/object.hpp>
#include <javabind/detail/peer_info.hpp>

namespace javabind {

template <typename T>
T& get_peer(object obj)
{
  field<jlong> peer_field = obj.class_().find_field<jlong>("peer");
  jlong peer = peer_field.get(obj);
  assert(peer != 0);
  detail::peer_info<T>* info = reinterpret_cast<detail::peer_info<T>*>(peer);
  return info->self;
}

template <typename T>
T& get_peer(JNIEnv* env, jobject obj)
{
  return get_peer<T>(object(obj, env));
}

}

#endif
