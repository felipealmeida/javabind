// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

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
  field<long_> peer;
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
    long_ peer = peer_field.get(javabind::object(base_ref, env));
    assert(peer != 0);
    javabind::detail::peer_info<T>* info
      = reinterpret_cast<javabind::detail::peer_info<T>*>(peer.raw());
    return info->self;
  }
  T& base(JNIEnv* env)
  {
    return const_cast<T&>(const_cast<extends<T>const&>(*this).base(env));
  }
private:
  field<long_> peer_field;
  jobject base_ref;
};

}

using extends_adl_protect::extends;
using extends_adl_protect::extends_info;

} }

#include <javabind/detail/peer_info.hpp>

#endif
