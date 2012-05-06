// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_ARRAY_HPP
#define JAVABIND_ARRAY_HPP

#include <javabind/primitives.hpp>
#include <javabind/object.hpp>

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

template <typename T>
struct array;

namespace array_detail {

template <typename JavaArray, typename JavaT, typename CxxT>
struct array_impl
{
  typedef JavaArray java_type;
  typedef array_impl<JavaArray, JavaT, CxxT> self_type;

  array_impl() : ar(0), env(0) {}
  array_impl(JavaArray ar, JNIEnv* env)
    : ar(ar), env(env) {}

  typedef array_region<JavaArray, JavaT, CxxT> region_type;

  region_type all() const
  {
    JavaT* raw = env->GetCharArrayElements(ar, 0);
    if(!raw)
      throw std::runtime_error("A exception was thrown");
    return region_type(raw, ar, env, length());
  }

  JavaArray raw() const { return ar; }
  std::size_t length() const
  {
    return env->GetArrayLength(ar);
  }

  typedef bool(self_type::*test_type)() const;
  operator test_type() const
  {
    return test()? &self_type::test : test_type(0);
  }
private:
  bool test() const { return ar != 0; }

  JavaArray ar;
  JNIEnv* env;
};

}

template <>
struct array<byte> : array_detail::array_impl<jbyteArray, jbyte, byte>
{
  typedef array_detail::array_impl<jbyteArray, jbyte, byte> base_type;

  array() {}
  array(jbyteArray ar, JNIEnv* env)
    : base_type(ar, env)
  {
  }
};

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

template <>
struct array<object> : array_detail::array_impl<jobjectArray, jobject, object>
{
  typedef array_detail::array_impl<jobjectArray, jobject, object> base_type;

  array() {}
  array(jobjectArray ar, JNIEnv* env)
    : base_type(ar, env)
  {
  }
};

}

#endif
