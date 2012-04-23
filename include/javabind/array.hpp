// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_ARRAY_HPP
#define JAVABIND_ARRAY_HPP

#include <javabind/primitives.hpp>

#include <cassert>
#include <stdexcept>

namespace javabind {

template <typename JavaArray, typename JavaT, typename CxxT>
struct array_region
{
  array_region(JavaT* raw_ar, JavaArray ar, JNIEnv* env
               , std::size_t size)
    : raw_ar(raw_ar), ar(ar), env(env)
    , size(size)
  {
  }
  ~array_region()
  {
    env->ReleaseCharArrayElements(ar, raw_ar, 0);
  }

  typedef JavaT const* raw_iterator;

  raw_iterator raw_begin() const { return raw_ar; }
  raw_iterator raw_end() const { return raw_ar + size; }

  CxxT operator[](std::size_t s) const
  {
    assert(s < size);
    return raw_ar[s];
  }
private:
  JavaT* raw_ar;
  JavaArray ar;
  JNIEnv* env;
  std::size_t size;
};

namespace array_detail {

template <typename JavaArray, typename JavaT, typename CxxT>
struct array_impl
{
  typedef JavaArray java_type;

  array_impl() : ar(0), env(0) {}
  array_impl(JavaArray ar, JNIEnv* env)
    : ar(ar), env(env) {}

  typedef array_region<JavaArray, JavaT, CxxT> region_type;

  region_type all() const
  {
    JavaT* raw = env->GetCharArrayElements(ar, 0);
    if(!raw)
      throw std::runtime_error("A exception was thrown");
    return region_type(raw, ar, env, env->GetArrayLength(ar));
  }
private:
  JavaArray ar;
  JNIEnv* env;
};

}

template <typename T>
struct array;

template <>
struct array<char_> : array_detail::array_impl<jcharArray, jchar, char_>
{
  typedef array_detail::array_impl<jcharArray, jchar, char_> base_type;

  array() {}
  array(jcharArray ar, JNIEnv* env)
    : base_type(ar, env)
  {
  }
};

}

#endif
