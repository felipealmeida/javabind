// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_REG_EXTENDS_HPP
#define JAVABIND_REG_EXTENDS_HPP

#include <javabind/class.hpp>
#include <javabind/field.hpp>

#include <jni.h>

namespace javabind {

namespace detail {

template <typename T>
struct peer_info;

}

namespace reg {

namespace tag {

struct extends_tag {};

}

namespace extends_adl_protect {

struct extends_info
{
  field<jlong> peer;
  jobject base; // weak reference
};

template <typename T>
struct extends : tag::extends_tag
{
  typedef extends_info info;

  extends(info i)
  : peer_field(i.peer), base_ref(i.base)
  {
  }

  T const& base(JNIEnv* env) const
  {
    jlong peer = peer_field.get(object(base_ref, env));
    assert(peer != 0);
    detail::peer_info<T>* info = reinterpret_cast<detail::peer_info<T>*>(peer);
    return info->self;
  }
  T& base(JNIEnv* env)
  {
    return const_cast<T&>(const_cast<extends<T>const&>(*this).base(env));
  }
private:
  field<jlong> peer_field;
  jobject base_ref;
};

}

using extends_adl_protect::extends;

} }

#endif
