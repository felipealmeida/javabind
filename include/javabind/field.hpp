// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_FIELD_HPP
#define JAVABIND_FIELD_HPP

#include <javabind/detail/tag.hpp>
#include <javabind/detail/get_static_field.hpp>

namespace javabind {

struct class_;

template <typename T>
struct static_field
{
  static_field( ::jfieldID id, JNIEnv* env)
    : id(id), env(env)
  {}

  T get(class_ const& cls) const
  {
    return detail::get_static_field(env, cls.cls, id, detail::tag<T>());
  }

  jfieldID id;
  JNIEnv* env;
};

}

#endif
