// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JAVABIND_DETAIL_OVERLOAD_SET_HPP
#define JAVABIND_DETAIL_OVERLOAD_SET_HPP

#include <javabind/detail/max_args.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace javabind { namespace detail {

template <typename Derived, int N, typename ArgSeq, typename R, typename F>
struct overload_set;

} }

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JAVABIND_MAX_ARGS), "javabind/detail/overload_set.hpp"))
#include BOOST_PP_ITERATE ()

#endif
#else

namespace javabind { namespace detail {

#define JAVABIND_OVERLOAD_SET_repeat_operator(z, n, data)               \
  BOOST_PP_COMMA_IF(n)                                                  \
  typename boost::mpl::deref<typename boost::mpl::advance               \
                             <typename boost::mpl::begin<ArgSeq>::type  \
                              , boost::mpl::size_t<n> >::type>::type    \
  BOOST_PP_CAT(a, n)

template <typename Derived, typename ArgSeq, typename F>
struct overload_set<Derived, BOOST_PP_ITERATION(), ArgSeq, void, F>
{
  BOOST_MPL_ASSERT_RELATION(boost::mpl::size<ArgSeq>::type::value, ==, BOOST_PP_ITERATION());
  overload_set(F f = F()) : f(f) {}
  typedef void result_type;
  void operator()(BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JAVABIND_OVERLOAD_SET_repeat_operator, ~)) const
  {
    f(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
  }

  F f;

  F functor() const { return f; }
};

template <typename Derived, typename ArgSeq, typename R, typename F>
struct overload_set<Derived, BOOST_PP_ITERATION(), ArgSeq, R, F>
{
  BOOST_MPL_ASSERT_RELATION((boost::mpl::size<ArgSeq>::type::value), ==, BOOST_PP_ITERATION());
  overload_set(F f = F()) : f(f) {}
  typedef R result_type;
  R operator()(BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JAVABIND_OVERLOAD_SET_repeat_operator, ~)) const
  {
    return f(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
  }

  F f;

  F functor() const { return f; }
};
#undef JAVABIND_OVERLOAD_SET_repeat_operator

} }

#endif

