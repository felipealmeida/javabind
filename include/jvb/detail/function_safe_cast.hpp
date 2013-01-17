// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FUNCTION_SAFE_CAST_HPP
#define JVB_DETAIL_FUNCTION_SAFE_CAST_HPP

#include <jvb/environment.hpp>
#include <jvb/primitives.hpp>
#include <jvb/array.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/is_function_pointer.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_same.hpp>

#include <jni.h>

namespace jvb { namespace detail {

namespace mpl = boost::mpl;

typedef boost::mpl::vector20<jboolean, jbyte, jchar, jshort, jint, jlong, jfloat
                             , jdouble, jobject, jclass, jbooleanArray, jbyteArray
                             , jcharArray, jshortArray, jintArray, jlongArray
                             , jfloatArray, jdoubleArray, jstring, void> allowed_types_seq;

typedef boost::mpl::vector20<bool, byte, char_, short_, int_, long_, float_
                             , double_, object, class_, array<bool>, array<byte>
                             , array<char_>, array<short_>, array<int_>, array<long_>
                             , array<float_>, array<double_>, string, void>
  allowed_cpp_types_seq;

template <typename T, typename AllowedTypes>
struct check_safe_type
  : mpl::or_
  <
    boost::mpl::contains
    <AllowedTypes
     , T
     >
    , boost::is_pointer<T>
  >
{
};

template <typename Iter, typename EndIter, typename AllowedTypes>
struct function_safe_cast_check_type : check_safe_type<typename boost::mpl::deref<Iter>::type, AllowedTypes>
{
  function_safe_cast_check_type<typename boost::mpl::next<Iter>::type, EndIter
                                , AllowedTypes> v1;
  check_safe_type<typename boost::mpl::deref<Iter>::type, AllowedTypes> v2;
  typedef function_safe_cast_check_type<Iter, EndIter, AllowedTypes> type;
};

template <typename EndIter, typename AllowedTypes>
struct function_safe_cast_check_type<EndIter, EndIter, AllowedTypes> {};

template <typename Sig, typename F>
void* function_safe_cast(F f)
{
  BOOST_MPL_ASSERT((boost::function_types::is_function_pointer<F>));

  typedef typename boost::function_types::result_type<F>::type result_type;
  typedef typename boost::function_types::parameter_types<F>::type parameter_types;

  typedef typename boost::function_types::result_type<Sig>::type result_sig_type;
  typedef typename boost::function_types::parameter_types<Sig>::type parameter_sig_types;

  BOOST_MPL_ASSERT((boost::mpl::not_<typename boost::mpl::empty<parameter_types>::type>));
  BOOST_MPL_ASSERT((boost::is_same
                    <
                      typename boost::mpl::deref
                      <typename boost::mpl::begin<parameter_types>::type>::type
                    , JNIEnv*
                    >));
  BOOST_MPL_ASSERT((boost::is_same
                    <
                      typename boost::mpl::deref
                      <typename boost::mpl::begin<parameter_sig_types>::type>::type
                    , environment
                    >));
  BOOST_MPL_ASSERT((mpl::equal_to
                    <typename mpl::size<parameter_sig_types>::type
                    , typename mpl::size<parameter_types>::type>));
  typedef typename boost::mpl::pop_front<parameter_types>::type test_parameter_types;

  typedef check_safe_type<result_type, allowed_types_seq> result_type_check;
  result_type_check v1; (void)v1;
  typedef function_safe_cast_check_type
  <typename boost::mpl::begin<test_parameter_types>::type
   , typename boost::mpl::end<test_parameter_types>::type
   , allowed_types_seq>
    parameter_types_check;
  BOOST_MPL_ASSERT((parameter_types_check));

  return reinterpret_cast<void*>(f);
}

} }

#endif
