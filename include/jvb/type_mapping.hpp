// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_TYPE_MAPPING_HPP
#define JVB_TYPE_MAPPING_HPP

#include <jvb/primitives.hpp>
#include <jvb/object.hpp>
#include <jvb/class.hpp>
#include <jvb/string.hpp>
#include <jvb/array.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <jni.h>

namespace jvb {


template <typename T, typename Enabler = void>
struct type_mapping;

template <typename T>
struct type_mapping<T// , typename boost::enable_if
                    // <boost::is_base_of<jvb::class_, T>, void>::type
                    >
{
  typedef jvb::class_ java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<void, void>
{
  typedef void java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<bool, void>
{
  typedef jboolean java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<byte, void>
{
  typedef byte::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<char_, void>
{
  typedef char_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<short_, void>
{
  typedef short_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<int_, void>
{
  typedef int_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<long_, void>
{
  typedef long_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<float_, void>
{
  typedef float_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<double_, void>
{
  typedef double_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<object, void>
{
  typedef jobject java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<string, void>
{
  typedef string::java_type java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

// template <>
// struct type_mapping<class_>
// {
//   typedef class_::java_type java_type;
//   typedef boost::mpl::false_ is_primitive;
//   typedef boost::mpl::false_ is_array;
// };

template <>
struct type_mapping<array<bool>, void>
{
  typedef jbooleanArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<byte>, void>
{
  typedef jbyteArray java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<char_>, void>
{
  typedef jcharArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<short_>, void>
{
  typedef jshortArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<int_>, void>
{
  typedef jintArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<long_>, void>
{
  typedef jlongArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<float_>, void>
{
  typedef jfloatArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<double_>, void>
{
  typedef jdoubleArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<object>, void>
{
  typedef jobjectArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

}

#endif
