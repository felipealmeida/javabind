// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ARRAY_HPP
#define JVB_ARRAY_HPP

#include <jvb/primitives.hpp>
#include <jvb/object.hpp>
#include <jvb/detail/array_functions.hpp>

#include <cassert>
#include <stdexcept>

namespace jvb {

template <typename JavaArray, typename JT, typename CT>
struct array_region
{
  array_region(JT* raw_ar, JavaArray ar, environment e
               , std::size_t size)
    : raw_ar(raw_ar), ar(ar), e(e)
    , size(size)
  {
  }
  ~array_region()
  {
    detail::array_functions<CT>::release_array_elements(e, ar, raw_ar, 0);
  }

  typedef JT const* raw_iterator;

  raw_iterator raw_begin() const { return raw_ar; }
  raw_iterator raw_end() const { return raw_ar + size; }

  CT operator[](std::size_t s) const
  {
    assert(s < size);
    return raw_ar[s];
  }
private:
  JT* raw_ar;
  JavaArray ar;
  environment e;
  std::size_t size;
};

template <typename T>
struct array;

namespace array_detail {

template <typename JavaArray, typename JT, typename CT>
struct array_impl
{
  typedef JavaArray java_type;
  typedef array_impl<JavaArray, JT, CT> self_type;

  array_impl() : ar(0) {}
  array_impl(JavaArray ar)
    : ar(ar) {}

  typedef array_region<JavaArray, JT, CT> region_type;

  region_type all(environment e) const
  {
    JT* raw = detail::array_functions<CT>::get_array_elements(e, ar, 0);
    if(!raw)
      throw std::runtime_error("A exception was thrown");
    return region_type(raw, ar, e, length(e));
  }

  JavaArray raw() const { return ar; }
  std::size_t length(environment e) const
  {
    return e.raw()->GetArrayLength(ar);
  }
  void set(environment e, JT const* raw_ar, std::size_t size)
  {
    detail::array_functions<CT>::set_array_region(e, ar, 0, size, raw_ar);
  }

  typedef bool(self_type::*test_type)() const;
  operator test_type() const
  {
    return test()? &self_type::test : test_type(0);
  }
private:
  bool test() const { return ar != 0; }

  JavaArray ar;
};

}

template <>
struct array<byte> : array_detail::array_impl<jbyteArray, jbyte, byte>
{
  typedef array_detail::array_impl<jbyteArray, jbyte, byte> base_type;

  array() {}
  array(environment e, jbyteArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<char_> : array_detail::array_impl<jcharArray, jchar, char_>
{
  typedef array_detail::array_impl<jcharArray, jchar, char_> base_type;

  array() {}
  array(environment e, jcharArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<object> : array_detail::array_impl<jobjectArray, jobject, object>
{
  typedef array_detail::array_impl<jobjectArray, jobject, object> base_type;

  array() {}
  array(environment e, jobjectArray ar)
    : base_type(ar)
  {
  }
};

}

#endif
