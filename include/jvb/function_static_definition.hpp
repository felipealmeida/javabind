// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#ifndef JVB_FUNCTION_STATIC_DEFINITION_HPP
#define JVB_FUNCTION_STATIC_DEFINITION_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/function_constrainer.hpp>
#include <jvb/environment.hpp>
#include <jvb/static_method.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

#include <boost/function_types/result_type.hpp>

namespace jvb {

template <typename F, typename Sig, typename C>
struct function_static_definition_object
{
  function_static_definition_object(jclass cls)
    : cls(cls) {}

  typedef Sig sig_type;
  typedef typename boost::function_types::result_type<sig_type>::type result_type;
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, JVB_MAX_ARGS, "jvb/function_static_definition.hpp"))
#include BOOST_PP_ITERATE()
  
  jclass cls;
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
  static_method<sig_type> m(e, cls, F::name());
  return m(e BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

#endif
