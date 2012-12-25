// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_FUNCTION_SAFE_CAST_HPP
#define JVB_DETAIL_FUNCTION_SAFE_CAST_HPP

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

#include <boost/type_traits/is_same.hpp>

namespace jvb { namespace detail {

typedef boost::mpl::vector20<jboolean, jbyte, jchar, jshort, jint, jlong, jfloat
                             , jdouble, jobject, jclass, jbooleanArray, jbyteArray
                             , jcharArray, jshortArray, jintArray, jlongArray
                             , jfloatArray, jdoubleArray, jstring, void> allowed_types_seq;

template <typename T>
struct check_safe_type
{
  BOOST_MPL_ASSERT((mpl::or_
                    <
                      boost::mpl::contains
                      <allowed_types_seq
                       , T
                      >
                    , boost::is_pointer<T>
                    >));
};

template <typename Iter, typename EndIter>
struct function_safe_cast_check_type
{
  function_safe_cast_check_type<typename boost::mpl::next<Iter>::type, EndIter> v1;
  check_safe_type<typename boost::mpl::deref<Iter>::type> v2;
};

template <typename EndIter>
struct function_safe_cast_check_type<EndIter, EndIter> {};

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

  typedef check_safe_type<result_type> result_type_check;
  result_type_check v1; (void)v1;
  typedef function_safe_cast_check_type
  <typename boost::mpl::begin<test_parameter_types>::type
   , typename boost::mpl::end<test_parameter_types>::type>
    parameter_types_check;
  parameter_types_check v2; (void)v2;

  return reinterpret_cast<void*>(f);
}

} }

#endif
