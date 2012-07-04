// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JVB_DETAIL_NATIVE_FUNCTIONS_HPP
#define JVB_DETAIL_NATIVE_FUNCTIONS_HPP

#include <jvb/detail/max_args.hpp>

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

#define JVB_DETAIL_NATIVE_FUNCTIONS_unwrap(x) jvb::detail::unwrap( x )
#define JVB_DETAIL_NATIVE_FUNCTIONS_is_static false

// #define JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function true
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param false
#define JVB_DETAIL_NATIVE_FUNCTIONS_function_name native_function
// #define JVB_DETAIL_NATIVE_FUNCTIONS_call() ((info->self).*(*f))
#define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n)
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, /*BOOST_PP_DEC (JVB_MAX_ARGS)*/0, "jvb/detail/native_functions.hpp"))
#include BOOST_PP_ITERATE ()

// #undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param true
// #define JVB_DETAIL_NATIVE_FUNCTIONS_function_name wrapper_with_env_member_native
// #define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n) env BOOST_PP_COMMA_IF(n)
// #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/native_functions.hpp"))
// #include BOOST_PP_ITERATE ()

// #undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_call
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param
// #define JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function false
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param false
// #define JVB_DETAIL_NATIVE_FUNCTIONS_function_name native_functions
// #define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n) info->self BOOST_PP_COMMA_IF(n)
// #define JVB_DETAIL_NATIVE_FUNCTIONS_call() (*f)
// #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/native_functions.hpp"))
// #include BOOST_PP_ITERATE ()

// #undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param true
// #define JVB_DETAIL_NATIVE_FUNCTIONS_function_name wrapper_with_env_native
// #define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n) info->self, env BOOST_PP_COMMA_IF(n)
// #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/native_functions.hpp"))
// #include BOOST_PP_ITERATE ()

// #define JVB_DETAIL_NATIVE_FUNCTIONS_void_return

// #undef JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_call
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_unwrap
// #define JVB_DETAIL_NATIVE_FUNCTIONS_unwrap(x) x

// #define JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function true
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param false
// #define JVB_DETAIL_NATIVE_FUNCTIONS_function_name wrapper_member_native_void
// #define JVB_DETAIL_NATIVE_FUNCTIONS_call() ((info->self).*(*f))
// #define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n)
// #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/native_functions.hpp"))
// #include BOOST_PP_ITERATE ()

// #undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param true
// #define JVB_DETAIL_NATIVE_FUNCTIONS_function_name wrapper_with_env_member_native_void
// #define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n) env BOOST_PP_COMMA_IF(n)
// #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/native_functions.hpp"))
// #include BOOST_PP_ITERATE ()

// #undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_call
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param
// #define JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function false
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param false
// #define JVB_DETAIL_NATIVE_FUNCTIONS_function_name native_functions_void
// #define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n) info->self BOOST_PP_COMMA_IF(n)
// #define JVB_DETAIL_NATIVE_FUNCTIONS_call() (*f)
// #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/native_functions.hpp"))
// #include BOOST_PP_ITERATE ()

// #undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
// #undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param
// #define JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param true
// #define JVB_DETAIL_NATIVE_FUNCTIONS_function_name wrapper_with_env_native_void
// #define JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(n) info->self, env BOOST_PP_COMMA_IF(n)
// #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/native_functions.hpp"))
// #include BOOST_PP_ITERATE ()

#undef JVB_DETAIL_NATIVE_FUNCTIONS_void_return
#undef JVB_DETAIL_NATIVE_FUNCTIONS_unwrap
#undef JVB_DETAIL_NATIVE_FUNCTIONS_is_static
#undef JVB_DETAIL_NATIVE_FUNCTIONS_function_name
#undef JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args
#undef JVB_DETAIL_NATIVE_FUNCTIONS_call
#undef JVB_DETAIL_NATIVE_FUNCTIONS_is_member_function
#undef JVB_DETAIL_NATIVE_FUNCTIONS_env_first_param

#endif
#else

namespace jvb { namespace detail {

// #ifdef JVB_DETAIL_NATIVE_FUNCTIONS_void_return
// #define JVB_DETAIL_NATIVE_FUNCTIONS_return_template_param
// #define JVB_DETAIL_NATIVE_FUNCTIONS_return_type void
// #else
// #define JVB_DETAIL_NATIVE_FUNCTIONS_return_template_param typename R, 
// #define JVB_DETAIL_NATIVE_FUNCTIONS_return_type R
// #endif

template <typename F, typename ParamSeq
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
void native_function
  (JNIEnv* env, jobject self_internal
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  F()(env, jvb::Object(env, self_internal)
      BOOST_PP_COMMA_IF(BOOST_PP_ITERATION())
      BOOST_PP_REPEAT(BOOST_PP_ITERATION() 
                      , JVB_DETAIL_NATIVE_FUNCTIONS_wrap_argument, 0));
  // assert(peer != 0);
  // peer_info<T>* info = reinterpret_cast<peer_info<T>*>(peer);
  // F const* f = static_cast<F const*>(info->bootstrap_info->vtable[index]);
  // return JVB_DETAIL_NATIVE_FUNCTIONS_unwrap(JVB_DETAIL_NATIVE_FUNCTIONS_call()
  //   ( 
  //    JVB_DETAIL_NATIVE_FUNCTIONS_complementary_args(BOOST_PP_ITERATION())
  //    BOOST_PP_REPEAT(BOOST_PP_ITERATION() 
  //                     , JVB_DETAIL_NATIVE_FUNCTIONS_wrap_argument, 0) ))
  //   ;
}

#undef JVB_DETAIL_NATIVE_FUNCTIONS_wrap_argument

#undef JVB_DETAIL_NATIVE_FUNCTIONS_seq_elem
#undef JVB_DETAIL_NATIVE_FUNCTIONS_return_template_param
#undef JVB_DETAIL_NATIVE_FUNCTIONS_return_type

} }

#endif
