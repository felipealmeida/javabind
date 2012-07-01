// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_FIELD_DESCRIPTOR_TRAITS_HPP
#define JVB_FIELD_DESCRIPTOR_TRAITS_HPP

#include <jvb/primitives.hpp>
#include <jvb/string.hpp>
#include <jvb/array.hpp>

#include <string>
#include <jni.h>

namespace jvb {

template <typename T>
struct field_descriptor_traits;

template <>
struct field_descriptor_traits<string>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<int_>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<char_>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<byte>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<double_>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<long_>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<bool>
{
  static const char* value;
};

// template <>
// struct field_descriptor_traits<array<char_> >
// {
//   static const char* value;
// };

template <>
struct field_descriptor_traits<void>
{
  static const char* value;
};

// template <>
// struct field_descriptor_traits<boolean> : field_descriptor_traits<boolean::java_type> {};
// template <>
// struct field_descriptor_traits<byte> : field_descriptor_traits<byte::java_type> {};
// template <>
// struct field_descriptor_traits<char_> : field_descriptor_traits<char_::java_type> {};
// template <>
// struct field_descriptor_traits<short_> : field_descriptor_traits<short_::java_type> {};
// template <>
// struct field_descriptor_traits<int_> : field_descriptor_traits<int_::java_type> {};
// template <>
// struct field_descriptor_traits<long_> : field_descriptor_traits<long_::java_type> {};
// template <>
// struct field_descriptor_traits<float_> : field_descriptor_traits<float_::java_type> {};
// template <>
// struct field_descriptor_traits<double_> : field_descriptor_traits<double_::java_type> {};

}

#endif
