// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JAVABIND_DETAIL_CALL_INT_METHOD_FUNCTOR_HPP
#define JAVABIND_DETAIL_CALL_INT_METHOD_FUNCTOR_HPP

#include <javabind/primitives.hpp>
#include <javabind/detail/max_args.hpp>
#include <javabind/detail/unwrap.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#include <stdexcept>

namespace javabind { namespace detail {

struct call_int_method_functor
{
  call_int_method_functor(jmethodID id)
    : id(id) {}
  typedef javabind::int_ result_type;

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/call_int_method_functor.hpp"))
#include BOOST_PP_ITERATE ()

  jmethodID raw() const { return id; }

  jmethodID id;
};

} }

#endif
#else

template <typename O BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
result_type operator()(O o BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  jint r 
    = o.environment()->CallIntMethod(o.raw(), id
                                     BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                                     , JAVABIND_TRAILING_UNWRAP, a));
  if(o.environment()->ExceptionCheck())
  {
    throw std::runtime_error("Exception was thrown");
  }
  return r;
}

#endif
