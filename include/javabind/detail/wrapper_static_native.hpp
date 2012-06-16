// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JAVABIND_DETAIL_WRAPPER_STATIC_NATIVE_HPP
#define JAVABIND_DETAIL_WRAPPER_STATIC_NATIVE_HPP

#include <javabind/detail/max_args.hpp>
#include <javabind/detail/wrap_argument.hpp>
#include <javabind/detail/unwrap.hpp>
#include <javabind/detail/bootstrap_info.hpp>
#include <javabind/detail/peer_info.hpp>
#include <javabind/detail/tag.hpp>
#include <javabind/detail/wrapper_native_cast_fwd.hpp>
#include <javabind/detail/wrapper_result_type.hpp>
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
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

#include <boost/utility/enable_if.hpp>

#include <stdexcept>

#define JAVABIND_DETAIL_WRAPPER_NATIVE_unwrap(x) javabind::detail::unwrap( x )
#define JAVABIND_DETAIL_WRAPPER_NATIVE_is_static true

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_call
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_is_member_function
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param
#define JAVABIND_DETAIL_WRAPPER_NATIVE_is_member_function false
#define JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param false
#define JAVABIND_DETAIL_WRAPPER_NATIVE_function_name wrapper_static_native
#define JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args(n) 
#define JAVABIND_DETAIL_WRAPPER_NATIVE_call() (*f)
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/wrapper_static_native.hpp"))
#include BOOST_PP_ITERATE ()

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param
#define JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param true
#define JAVABIND_DETAIL_WRAPPER_NATIVE_function_name wrapper_with_env_static_native
#define JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args(n) env BOOST_PP_COMMA_IF(n)
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/wrapper_static_native.hpp"))
#include BOOST_PP_ITERATE ()

#define JAVABIND_DETAIL_WRAPPER_NATIVE_void_return

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_is_member_function
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_call
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_unwrap
#define JAVABIND_DETAIL_WRAPPER_NATIVE_unwrap(x) x

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_call
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_is_member_function
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param
#define JAVABIND_DETAIL_WRAPPER_NATIVE_is_member_function false
#define JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param false
#define JAVABIND_DETAIL_WRAPPER_NATIVE_function_name wrapper_static_native_void
#define JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args(n) 
#define JAVABIND_DETAIL_WRAPPER_NATIVE_call() (*f)
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/wrapper_static_native.hpp"))
#include BOOST_PP_ITERATE ()

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param
#define JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param true
#define JAVABIND_DETAIL_WRAPPER_NATIVE_function_name wrapper_with_env_static_native_void
#define JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args(n) env BOOST_PP_COMMA_IF(n)
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/wrapper_static_native.hpp"))
#include BOOST_PP_ITERATE ()

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_unwrap
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_is_static
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_call
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_is_member_function
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param

#endif
#else

namespace javabind { namespace detail {

#define JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument(z, n, trailing_comma) \
    BOOST_PP_COMMA_IF(BOOST_PP_ADD(n, trailing_comma))                  \
    wrap_argument<typename boost::mpl::at_c<ParamSeq, BOOST_PP_INC(n)>::type> \
    (BOOST_PP_CAT(a, n), env)

#ifdef JAVABIND_DETAIL_WRAPPER_NATIVE_void_return
#define JAVABIND_DETAIL_WRAPPER_NATIVE_return_template_param
#define JAVABIND_DETAIL_WRAPPER_NATIVE_return_type void
#else
#define JAVABIND_DETAIL_WRAPPER_NATIVE_return_template_param typename R, 
#define JAVABIND_DETAIL_WRAPPER_NATIVE_return_type R
#endif

template <std::size_t index, typename T,
          JAVABIND_DETAIL_WRAPPER_NATIVE_return_template_param
          typename F, typename ParamSeq
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
JAVABIND_DETAIL_WRAPPER_NATIVE_return_type JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
  (JNIEnv* env, jclass self_internal, jlong bootstrap
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  assert(bootstrap != 0);
  bootstrap_info* info = reinterpret_cast<bootstrap_info*>(bootstrap);
  F const* f = static_cast<F const*>(info->vtable[index]);
  return JAVABIND_DETAIL_WRAPPER_NATIVE_unwrap(JAVABIND_DETAIL_WRAPPER_NATIVE_call()
    ( 
     JAVABIND_DETAIL_WRAPPER_NATIVE_complementary_args(BOOST_PP_ITERATION())
     BOOST_PP_REPEAT(BOOST_PP_ITERATION() 
                      , JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument, 0) ))
    ;
}

#undef JAVABIND_DETAIL_WRAPPER_NATIVE_wrap_argument

#define JAVABIND_DETAIL_WRAPPER_NATIVE_seq_elem(z, n, data) \
    , typename type_mapping<typename boost::mpl::at_c<S, n+1>::type>::java_type

template <JAVABIND_DETAIL_WRAPPER_NATIVE_return_template_param typename S>
struct wrapper_native_cast<JAVABIND_DETAIL_WRAPPER_NATIVE_return_type
  , S, JAVABIND_DETAIL_WRAPPER_NATIVE_is_member_function
  , JAVABIND_DETAIL_WRAPPER_NATIVE_env_first_param
  , JAVABIND_DETAIL_WRAPPER_NATIVE_is_static, typename boost::enable_if_c
 <boost::mpl::size<S>::type::value-1 == BOOST_PP_ITERATION(), void>::type
>
{
  typedef detail::wrapper_result_type<JAVABIND_DETAIL_WRAPPER_NATIVE_return_type, S
                                      , JAVABIND_DETAIL_WRAPPER_NATIVE_is_static>
  wrapper_result_type;
  typedef typename wrapper_result_type::type result_type;
  typedef typename wrapper_result_type::call_result_type call_result_type;

  template <std::size_t index, typename T, typename F>
  static result_type call()
  {
    return static_cast<result_type>(& JAVABIND_DETAIL_WRAPPER_NATIVE_function_name
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
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_return_template_param
#undef JAVABIND_DETAIL_WRAPPER_NATIVE_return_type

} }

#endif
