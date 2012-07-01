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

// struct boolean
// {
//   typedef jboolean java_type;
//   boolean(java_type o) : o(o) {}

//   bool is_true() const { return o; }
//   typedef bool(boolean::* unspecified_boolean_type)() const;

//   operator unspecified_boolean_type() const
//   {
//     unspecified_boolean_type n = 0;
//     return is_true()? &boolean::is_true : n;
//   }
//   bool operator!() const { return !is_true(); }

//   java_type raw() const { return o; }
//   operator java_type() const { return o; }

// private:
//   java_type o;
// };

struct byte
{
  typedef jbyte java_type;
  byte(java_type o) : o(o) {}

  java_type raw() const { return o; }
  
private:
  java_type o;
};

struct char_
{
  typedef jchar java_type;
  char_(java_type o) : o(o) {}

  java_type raw() const { return o; }

private:
  java_type o;
};

struct short_tag {};
struct int_tag {};
struct long_tag {};
struct float_tag {};
struct double_tag {};

typedef number<jshort, short_tag> short_;
typedef number<jint, int_tag> int_;
typedef number<jlong, long_tag> long_;
typedef number<jfloat, float_tag> float_;
typedef number<jdouble, double_tag> double_;

}

#endif