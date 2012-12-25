// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JVB_DETAIL_NEW_OBJECT_FUNCTOR_HPP
#define JVB_DETAIL_NEW_OBJECT_FUNCTOR_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/unwrap.hpp>
#include <jvb/detail/hidden_object.hpp>
#include <jvb/class.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace jvb { namespace detail {

template <typename R>
struct new_object_functor
{
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/new_object_functor.hpp"))
#include BOOST_PP_ITERATE ()
};

} }

#endif
#else

#if BOOST_PP_ITERATION()
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
#endif
R operator()(environment e, Class const& cls, jmethodID id BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  jobject o = e.raw()->NewObject
    (cls.raw(), id BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                                   , JVB_TRAILING_UNWRAP, a));
  if(o)
    return R(hidden_object(o));
  throw std::runtime_error("Exception throw while constructing a object");
}

#endif
