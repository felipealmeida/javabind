// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_PRIMITIVES_HPP
#define JVB_PRIMITIVES_HPP

#include <jvb/number.hpp>

#include <ostream>

#include <jni.h>

namespace jvb {

struct byte_tag {};
struct char_tag {};
struct short_tag {};
struct int_tag {};
struct long_tag {};
struct float_tag {};
struct double_tag {};

typedef number<jbyte, byte_tag> byte;
typedef number<jchar, char_tag> char_;
typedef number<jshort, short_tag> short_;
typedef number<jshort, short_tag> short_;
typedef number<jint, int_tag> int_;
typedef number<jlong, long_tag> long_;
typedef number<jfloat, float_tag> float_;
typedef number<jdouble, double_tag> double_;

}

#endif
