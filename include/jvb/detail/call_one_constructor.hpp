// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JVB_DETAIL_CALL_ONE_CONSTRUCTOR_HPP
#define JVB_DETAIL_CALL_ONE_CONSTRUCTOR_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/unwrap.hpp>
#include <jvb/detail/overload_set.hpp>
#include <jvb/class.hpp>
#include <jvb/constructor_overload_definition.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace jvb { namespace detail {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/call_one_constructor.hpp"))
#include BOOST_PP_ITERATE ()

} }

#endif
#else
#define N BOOST_PP_ITERATION()

template <typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
R call_one_constructor(environment e BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, a))
{
  typedef typename R::all_constructors all_constructors;
  typedef constructor_overload_definition_object<R> constructor;
  constructor c;
  detail::overload_set<all_constructors, R, constructor>
    overload_set(c);
  return overload_set(e BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
}

#undef N
#endif
