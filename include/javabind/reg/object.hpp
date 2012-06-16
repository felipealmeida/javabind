// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_REG_OBJECT_HPP
#define JAVABIND_REG_OBJECT_HPP

#include <javabind/class.hpp>
#include <javabind/field.hpp>
#include <javabind/object.hpp>

#include <jni.h>

namespace javabind {

namespace detail {

template <typename T>
struct peer_info;

}

namespace reg {

namespace object_adl_protect {

struct object_info
{
  field<long_> peer;
  jobject ref; // weak reference
};

struct object
{
  typedef object_info info;

  object(info i)
  : ref(i.ref)
  {
  }

  javabind::object self(JNIEnv* env) const
  {
    return javabind::object(ref, env);
  }
private:
  jobject ref;
};

}

using object_adl_protect::object;
using object_adl_protect::object_info;

} }

#endif
