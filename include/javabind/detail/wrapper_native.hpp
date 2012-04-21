// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_HPP
#define JAVABIND_DETAIL_WRAPPER_NATIVE_HPP

#include <javabind/detail/max_args.hpp>
#include <javabind/detail/unwrap.hpp>
#include <javabind/detail/bootstrap_info.hpp>
#include <javabind/detail/peer_info.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#include <boost/function_types/function_pointer.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

#include <boost/utility/enable_if.hpp>

#include <stdexcept>

namespace javabind { namespace detail {

template <typename R, typename S>
struct wrapper_result_type
{
  typedef typename boost::function_types::function_pointer
  <typename boost::mpl::push_front // result
   <typename boost::mpl::push_front // JNIEnv*
    <typename boost::mpl::push_front // jobject self
     <S, jobject>::type
     , JNIEnv*>::type
    , R>::type>
  ::type type;
};

template <typename R, typename S, bool, bool, typename Enable = void>
struct wrapper_native_cast;

} }

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/wrapper_native.hpp"))
#include BOOST_PP_ITERATE ()

#endif
#else

namespace javabind { namespace detail {

template <std::size_t index, typename T, typename R, typename F
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
R wrapper_member_native(JNIEnv* env, jobject self_internal, jlong peer
                        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper member native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  return ((info->self).*(*f))( BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a) );
}

template <std::size_t index, typename T, typename R, typename F
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
R wrapper_with_env_member_native(JNIEnv* env, jobject self_internal, jlong peer
                                 BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper member native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  return ((info->self).*(*f))(env BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a) );
}

template <std::size_t index, typename T, typename R, typename F
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
R wrapper_native(JNIEnv* env, jobject self_internal, jlong peer
                    BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  R r = (*f)(info->self BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a) );
  //std::cout << "wrapper_native finished successful" << std::endl;
  return r;
}

template <std::size_t index, typename T, typename R, typename F
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
R wrapper_with_env_native(JNIEnv* env, jobject self_internal, jlong peer
                    BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  R r = (*f)(info->self, env BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a) );
  //std::cout << "wrapper_native finished successful" << std::endl;
  return r;
}

#define JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem(z, n, data) \
  , typename boost::mpl::at_c<S, n+1>::type

template <typename R, typename S>
struct wrapper_native_cast
<R, S, true, false, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
  typedef typename wrapper_result_type<R, S>::type result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(&wrapper_member_native
                                    <index, T, R, F
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

template <typename R, typename S>
struct wrapper_native_cast
<R, S, false, false, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
  typedef typename wrapper_result_type<R, S>::type result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(&wrapper_native
                                    <index, T, R, F
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

template <typename R, typename S>
struct wrapper_native_cast
<R, S, true, true, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
  typedef typename wrapper_result_type<R, S>::type result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(&wrapper_with_env_member_native
                                    <index, T, R, F
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

template <typename R, typename S>
struct wrapper_native_cast
<R, S, false, true, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
  typedef typename wrapper_result_type<R, S>::type result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(&wrapper_with_env_native
                                    <index, T, R, F
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem

} }

#endif
