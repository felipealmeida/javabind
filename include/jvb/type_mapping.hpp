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

template <>
struct type_mapping<void>
{
  typedef void java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <typename T>
struct type_mapping<T, typename boost::enable_if<boost::is_pointer<T> >::type>
{
  typedef ::jlong java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<bool>
{
  typedef jboolean java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<byte>
{
  typedef byte::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<char_>
{
  typedef char_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<short_>
{
  typedef short_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<int_>
{
  typedef int_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<long_>
{
  typedef long_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<float_>
{
  typedef float_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<double_>
{
  typedef double_::java_type java_type;
  typedef boost::mpl::true_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<object>
{
  typedef jobject java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <typename T>
struct type_mapping<T, typename boost::enable_if<boost::is_base_of<jvb::object, T> >::type
                    > : type_mapping<jvb::object>
{
};

template <>
struct type_mapping<string>
{
  typedef string::java_type java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::false_ is_array;
};

template <>
struct type_mapping<array<bool> >
{
  typedef jbooleanArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<byte> >
{
  typedef jbyteArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<char_> >
{
  typedef jcharArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<short_> >
{
  typedef jshortArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<int_> >
{
  typedef jintArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<long_> >
{
  typedef jlongArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<float_> >
{
  typedef jfloatArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<double_> >
{
  typedef jdoubleArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <>
struct type_mapping<array<object> >
{
  typedef jobjectArray java_type;
  typedef boost::mpl::false_ is_primitive;
  typedef boost::mpl::true_ is_array;
};

template <typename T>
struct type_mapping<array<T>, typename boost::enable_if<boost::is_base_of<jvb::object, T> >::type
                    > : type_mapping<array<jvb::object> >
{
};

}

#endif
