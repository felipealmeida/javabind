// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_FIELD_DESCRIPTOR_TRAITS_HPP
#define JAVABIND_FIELD_DESCRIPTOR_TRAITS_HPP

#include <string>
#include <jni.h>

namespace javabind {

template <typename T>
struct field_descriptor_traits;

template <>
struct field_descriptor_traits<std::string>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<jint>
{
  static const char* value;
};

template <>
struct field_descriptor_traits<jdouble>
{
  static const char* value;
};

}

#endif
