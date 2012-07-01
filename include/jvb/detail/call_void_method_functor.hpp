// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JVB_DETAIL_CALL_VOID_METHOD_FUNCTOR_HPP
#define JVB_DETAIL_CALL_VOID_METHOD_FUNCTOR_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/unwrap.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#include <stdexcept>

namespace jvb { namespace detail {

struct call_void_method_functor
{
  call_void_method_functor(jobject obj, jmethodID id)
    : obj(obj), id(id) {}
  typedef void result_type;

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/call_void_method_functor.hpp"))
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
result_type operator()(jvb::environment e BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  e.raw()->CallVoidMethod(obj, id
                          BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                          , JVB_TRAILING_UNWRAP, a));
  if(e.raw()->ExceptionCheck())
  {
    throw std::runtime_error("Exception was thrown");
  }
}

#endif
