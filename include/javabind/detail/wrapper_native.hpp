// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_HPP
#define JAVABIND_DETAIL_WRAPPER_NATIVE_HPP

#include <javabind/detail/max_args.hpp>
#include <javabind/detail/wrap_argument.hpp>
#include <javabind/detail/unwrap.hpp>
#include <javabind/detail/bootstrap_info.hpp>
#include <javabind/detail/peer_info.hpp>
#include <javabind/detail/tag.hpp>
#include <javabind/type_mapping.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

#include <boost/function_types/function_pointer.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

#include <boost/mpl/transform.hpp>

#include <boost/utility/enable_if.hpp>

#include <stdexcept>

namespace javabind { namespace detail {

template <typename R, typename S>
struct wrapper_result_type
{
  struct transformation_op
  {
    template <typename T>
    struct apply
    {
      typedef typename type_mapping<T>::java_type type;
    };
  };

  typedef typename boost::mpl::apply_wrap1<transformation_op, R>::type
    call_result_type;

  typedef typename boost::function_types::function_pointer
  <typename boost::mpl::push_front // result
   <typename boost::mpl::push_front // JNIEnv*
    <typename boost::mpl::push_front // jobject self
     <typename boost::mpl::transform<S, transformation_op>::type
      , jobject>::type
     , JNIEnv*>::type
    , call_result_type
    >::type
   >::type type;
};

template <typename R, typename S, bool, bool, typename Enable = void>
struct wrapper_native_cast;

} }

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/wrapper_native.hpp"))
#include BOOST_PP_ITERATE ()
#define JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/wrapper_native.hpp"))
#include BOOST_PP_ITERATE ()
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return

#endif
#else

namespace javabind { namespace detail {

#define JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument(z, n, trailing_comma) \
    BOOST_PP_COMMA_IF(BOOST_PP_ADD(n, trailing_comma))                  \
    wrap_argument<typename boost::mpl::at_c<ParamSeq, BOOST_PP_INC(n)>::type> \
    (BOOST_PP_CAT(a, n), env)

template <std::size_t index, typename T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
          , typename R
#endif
          , typename F, typename ParamSeq
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
R wrapper_member_native
#else
void wrapper_member_native_void
#endif
  (JNIEnv* env, jobject self_internal, jlong peer
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper member native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  return
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    javabind::detail::unwrap(
#endif
    ((info->self).*(*f))
    ( BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                      , JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument, 0) )
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    )
#endif
    ;
}

template <std::size_t index, typename T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
          , typename R
#endif
          , typename F, typename ParamSeq
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
R wrapper_with_env_member_native
#else
void wrapper_with_env_member_native_void
#endif
 (JNIEnv* env, jobject self_internal, jlong peer
  BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper member native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  return
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    javabind::detail::unwrap(
#endif
    ((info->self).*(*f))
    (env BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                         , JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument, 1) )
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    )
#endif
    ;
}

template <std::size_t index, typename T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
          , typename R
#endif
          , typename F, typename ParamSeq
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
R wrapper_native
#else
void wrapper_native_void
#endif
 (JNIEnv* env, jobject self_internal, jlong peer
  BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  return 
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    javabind::detail::unwrap(
#endif
   (*f)(info->self BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                , JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument, 1) )
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    )
#endif
    ;
}

template <std::size_t index, typename T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
          , typename R
#endif
          , typename F, typename ParamSeq
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
R wrapper_with_env_native
#else
void wrapper_with_env_native_void
#endif
 (JNIEnv* env, jobject self_internal, jlong peer
  BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  //std::cout << "Wrapper native " << index << std::endl;
  assert(peer != 0);
  peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  //std::cout << "f: " << f << " F: " << typeid(F).name() << std::endl;
  return
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    javabind::detail::unwrap(
#endif
   (*f)(info->self, env BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                     , JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument, 1) )
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
    )
#endif
    ;
}

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument

#define JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem(z, n, data) \
    , typename type_mapping<typename boost::mpl::at_c<S, n+1>::type>::java_type

template <
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typename R,
#endif
  typename S>
struct wrapper_native_cast<
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  R
#else
  void
#endif
  , S, true, false, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
#ifdef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typedef void R;
#endif
  typedef detail::wrapper_result_type<R, S> wrapper_result_type;
  typedef typename wrapper_result_type::type result_type;
  typedef typename wrapper_result_type::call_result_type call_result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                    &wrapper_member_native
#else
                                    &wrapper_member_native_void
#endif
                                    <index, T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                     , call_result_type
#endif
                                     , F, S
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

template <
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typename R,
#endif
  typename S>
struct wrapper_native_cast<
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  R
#else
  void
#endif
  , S, false, false, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
#ifdef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typedef void R;
#endif
  typedef detail::wrapper_result_type<R, S> wrapper_result_type;
  typedef typename wrapper_result_type::type result_type;
  typedef typename wrapper_result_type::call_result_type call_result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                    &wrapper_native
#else
                                    &wrapper_native_void
#endif
                                    <index, T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                     , call_result_type
#endif
                                     , F, S
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

template <
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typename R,
#endif
  typename S>
struct wrapper_native_cast<
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  R
#else
  void
#endif
  , S, true, true, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
#ifdef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typedef void R;
#endif
  typedef detail::wrapper_result_type<R, S> wrapper_result_type;
  typedef typename wrapper_result_type::type result_type;
  typedef typename wrapper_result_type::call_result_type call_result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                    &wrapper_with_env_member_native
#else
                                    &wrapper_with_env_member_native_void
#endif
                                    <index, T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                     , call_result_type
#endif
                                     , F, S
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

template <
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typename R,
#endif
  typename S>
struct wrapper_native_cast<
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  R
#else
  void
#endif
  , S, false, true, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
#ifdef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
  typedef void R;
#endif

  typedef detail::wrapper_result_type<R, S> wrapper_result_type;
  typedef typename wrapper_result_type::type result_type;
  typedef typename wrapper_result_type::call_result_type call_result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                    &wrapper_with_env_native
#else
                                    &wrapper_with_env_native_void
#endif
                                    <index, T
#ifndef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
                                     , call_result_type
#endif
                                     , F, S
                                    BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                    , JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem
                                                    , ~)>);
  }
};

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem

} }

#endif
