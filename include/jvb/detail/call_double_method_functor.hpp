// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JVB_DETAIL_CALL_DOUBLE_METHOD_FUNCTOR_HPP
#define JVB_DETAIL_CALL_DOUBLE_METHOD_FUNCTOR_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/unwrap.hpp>
#include <jvb/error.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#include <stdexcept>

namespace jvb { namespace detail {

struct call_double_method_functor
{
  call_double_method_functor(jobject obj, jmethodID id)
    : obj(obj), id(id) {}
  typedef double_ result_type;

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/call_double_method_functor.hpp"))
#include BOOST_PP_ITERATE ()

  jmethodID raw() const { return id; }

  jobject obj;
  jmethodID id;
};

} }

#endif
#else

#if BOOST_PP_ITERATION()
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
#endif
result_type operator()(environment e BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  jdouble r 
    = e.raw()->CallDoubleMethod(obj, id
                                BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                , JVB_TRAILING_UNWRAP, a));
  error::throw_exception(e);
  return r;
}

#endif
