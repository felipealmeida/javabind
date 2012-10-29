// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#ifndef JVB_FUNCTION_DEFINITION_HPP
#define JVB_FUNCTION_DEFINITION_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/function_constrainer.hpp>
#include <jvb/environment.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/function_types/result_type.hpp>

namespace jvb {

template <typename F, typename Sig, typename C>
struct function_definition_object
{
  function_definition_object(jobject obj)
    : obj(obj) {}

  typedef Sig sig_type;
  typedef typename boost::function_types::result_type<sig_type>::type result_type;
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, JVB_MAX_ARGS, "jvb/function_definition.hpp"))
#include BOOST_PP_ITERATE()

  jobject obj;
};

template <typename F, typename Sig, typename C>
struct function_definition
  : jvb::detail::function_constrainer
  <boost::mpl::size
   <typename boost::function_types::parameter_types<Sig>::type>::value + 1
   , boost::mpl::joint_view
     <
       boost::mpl::vector1<environment>
     , typename boost::function_types::parameter_types<Sig>::type
     >
   , typename boost::function_types::result_type<Sig>::type
   , function_definition_object<F, Sig, C>
  >
{
  typedef jvb::detail::function_constrainer
  <boost::mpl::size
   <typename boost::function_types::parameter_types<Sig>::type>::value + 1
   , boost::mpl::joint_view
     <
       boost::mpl::vector1<environment>
     , typename boost::function_types::parameter_types<Sig>::type
     >
   , typename boost::function_types::result_type<Sig>::type
   , function_definition_object<F, Sig, C>
  > base_type;

  function_definition(jobject o)
    : base_type(function_definition_object<F, Sig, C>(o)) {}
};

}

#endif
#else

#if BOOST_PP_ITERATION() != 0
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
#endif
result_type operator()(environment e
                       BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION()
                                                            , A, a)) const
{
  method<sig_type> m(e, obj, F::name());
  return m(e BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

#endif
