// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FIELD_HIDDEN_OBJECT_HPP
#define JVB_DETAIL_FIELD_HIDDEN_OBJECT_HPP

#include <jni.h>

namespace jvb { namespace detail {

struct hidden_object
{
  hidden_object(jobject obj)
    : obj(obj) {}

  jobject obj;
};

} }

#endif
