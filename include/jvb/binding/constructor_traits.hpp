// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING) || !BOOST_PP_IS_ITERATING

#ifndef JVB_BINDING_CONSTRUCTOR_TRAITS_HPP
#define JVB_BINDING_CONSTRUCTOR_TRAITS_HPP

#include <jvb/environment.hpp>
#include <jvb/detail/max_args.hpp>

#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/mem_fn.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/identity.hpp>

namespace jvb { namespace binding {

namespace mpl = boost::mpl;

template <typename F>
struct constructor_traits
{
  struct void_ { typedef void_ type; };

  typedef typename boost::function_types::result_type<F>::type result_type;
  typedef typename boost::function_types::parameter_types<F>::type parameter_types;
  typedef typename mpl::empty<parameter_types>::type empty_parameter_types;

  typedef typename mpl::eval_if
  <boost::mpl::empty<parameter_types>
   , void_
   , boost::mpl::at_c<parameter_types, 0>
  >::type arg0_type;

  // Peer class type: 
  //     ((arg0_type != void_ /\ arg0_type != environment) \/ is_member_function_pointer
  //      => peer_class = arg0_type)

  // has_environment:
  // has_environment = (arg1_type = environment \/ arg0_type = environment)

  typedef typename 
    boost::is_same<arg0_type, environment>
  has_environment;

  template <typename Func>
  struct function_caller
  {
    function_caller(Func f)
      : f(f) {}

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, JVB_MAX_ARGS, "jvb/binding/constructor_traits.hpp"))
#include BOOST_PP_ITERATE()

    Func f;
  };
};

} }
#endif
#else
#define N BOOST_PP_ITERATION()

template <typename FF
          BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
static result_type call_aux(FF f, environment e
                            , boost::mpl::false_
                            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, a))
{
  return f(BOOST_PP_ENUM_PARAMS(N, a));
}

template <typename FF
          BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
static result_type call_aux(FF f, environment e
                            , boost::mpl::true_
                            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, a))
{
  return f(e BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
}

#if N
template <BOOST_PP_ENUM_PARAMS(N, typename A)>
#endif
result_type operator()(environment e
                       BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, a))
{
  return call_aux(f, e, has_environment()
                   BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
}

#undef N
#endif
