// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ARRAY_HPP
#define JVB_ARRAY_HPP

#include <jvb/primitives.hpp>
#include <jvb/object.hpp>
#include <jvb/error.hpp>
#include <jvb/detail/array_functions.hpp>
#include <jvb/detail/hidden_object.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <cassert>
#include <stdexcept>

namespace jvb {

template <typename T, typename Enable = void>
struct array;

namespace array_detail {

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

template <typename JavaArray, typename JT, typename CT>
struct array_object_region
{
  array_object_region(JavaArray ar, environment e, std::size_t size)
    : ar(ar), e(e), size(size)
  {
  }
  ~array_object_region()
  {
  }

  CT operator[](std::size_t s) const
  {
    assert(s < size);
    JT obj = e.raw()->GetObjectArrayElement(ar, s);
    if(!obj) error::throw_exception(e);
    std::cout << "operator[" << s << "] " << static_cast<void*>(obj) << std::endl;
    return CT(detail::hidden_object(obj));
  }
private:
  JavaArray ar;
  environment e;
  std::size_t size;
};

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
    if(!raw) error::throw_exception(e);
    return region_type(raw, ar, e, length(e));
  }

  JavaArray raw() const { return ar; }
  std::size_t length(environment e) const
  {
    std::size_t l = e.raw()->GetArrayLength(ar);
    error::throw_exception(e);
    return l;
  }
  void set(environment e, JT const* raw_ar, std::size_t size)
  {
    detail::array_functions<CT>::set_array_region(e, ar, 0, size, raw_ar);
    error::throw_exception(e);
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

template <typename JavaArray, typename JT, typename CT>
struct array_object_impl
{
  typedef JavaArray java_type;
  typedef array_object_impl<JavaArray, JT, CT> self_type;

  array_object_impl() : ar(0) {}
  array_object_impl(JavaArray ar)
    : ar(ar) {}

  typedef array_object_region<JavaArray, JT, CT> region_type;

  region_type all(environment e) const
  {
    return region_type(ar, e, length(e));
  }

  JavaArray raw() const { return ar; }
  std::size_t length(environment e) const
  {
    std::size_t l = e.raw()->GetArrayLength(ar);
    error::throw_exception(e);
    return l;
  }
  void set(environment e, JT const* raw_ar, std::size_t size)
  {
    std::abort();
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
struct array<bool> : array_detail::array_impl<jbooleanArray, jboolean, bool>
{
  typedef array_detail::array_impl<jbooleanArray, jboolean, bool> base_type;

  array() {}
  array(jbooleanArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<byte> : array_detail::array_impl<jbyteArray, jbyte, byte>
{
  typedef array_detail::array_impl<jbyteArray, jbyte, byte> base_type;

  array() {}
  array(jbyteArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<char_> : array_detail::array_impl<jcharArray, jchar, char_>
{
  typedef array_detail::array_impl<jcharArray, jchar, char_> base_type;

  array() {}
  array(jcharArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<short_> : array_detail::array_impl<jshortArray, jshort, short_>
{
  typedef array_detail::array_impl<jshortArray, jshort, short_> base_type;

  array() {}
  array(jshortArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<int_> : array_detail::array_impl<jintArray, jint, int_>
{
  typedef array_detail::array_impl<jintArray, jint, int_> base_type;

  array() {}
  array(jintArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<long_> : array_detail::array_impl<jlongArray, jlong, long_>
{
  typedef array_detail::array_impl<jlongArray, jlong, long_> base_type;

  array() {}
  array(jlongArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<float_> : array_detail::array_impl<jfloatArray, jfloat, float_>
{
  typedef array_detail::array_impl<jfloatArray, jfloat, float_> base_type;

  array() {}
  array(jfloatArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<double_> : array_detail::array_impl<jdoubleArray, jdouble, double_>
{
  typedef array_detail::array_impl<jdoubleArray, jdouble, double_> base_type;

  array() {}
  array(jdoubleArray ar)
    : base_type(ar)
  {
  }
};

template <>
struct array<object> : array_detail::array_object_impl<jobjectArray, jobject, object>
{
  typedef array_detail::array_object_impl<jobjectArray, jobject, object> base_type;

  array() {}
  array(jobjectArray ar)
    : base_type(ar)
  {
  }
};

template <typename T>
struct array<T, typename boost::enable_if<boost::is_base_of<object, T> >::type>
  : array_detail::array_object_impl<jobjectArray, jobject, T>
{
  typedef array_detail::array_object_impl<jobjectArray, jobject, T> base_type;

  array() {}
  array(jobjectArray ar)
    : base_type(ar)
  {
  }
};

}

#endif
