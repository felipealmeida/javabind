// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JVB_DETAIL_FUNCTION_CONSTRAINER_HPP
#define JVB_DETAIL_FUNCTION_CONSTRAINER_HPP

#include <jvb/detail/max_args.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace jvb { namespace detail {

template <int N, typename ArgSeq, typename R, typename F>
struct function_constrainer;

template <int N, typename ArgSeqs, typename R, typename F>
struct function_constrainer_group
{};

} }

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (JVB_MAX_ARGS), "jvb/detail/function_constrainer.hpp"))
#include BOOST_PP_ITERATE ()

#endif
#else

namespace jvb { namespace detail {

#define JVB_FUNCTION_CONSTRAINER_base(z, n, data)                       \
    BOOST_PP_COMMA_IF(n)                                                \
    function_constrainer                                                \
    <boost::mpl::size<typename boost::mpl::at_c<ArgSeqs, n>::type>::type::value \
     , typename boost::mpl::at_c<ArgSeqs, n>::type                      \
     , R, F>
    
template <typename ArgSeqs, typename R, typename F>
struct function_constrainer_group<BOOST_PP_ITERATION(), ArgSeqs, R, F>
#if BOOST_PP_ITERATION() != 0
  : BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JVB_FUNCTION_CONSTRAINER_base, ~)
#endif
{
};

#define JVB_FUNCTION_CONSTRAINER_repeat_operator(z, n, data)               \
  BOOST_PP_COMMA_IF(n)                                                  \
  typename boost::mpl::deref<typename boost::mpl::advance               \
                             <typename boost::mpl::begin<ArgSeq>::type  \
                              , boost::mpl::size_t<n> >::type>::type    \
  BOOST_PP_CAT(a, n)

template <typename ArgSeq, typename F>
struct function_constrainer<BOOST_PP_ITERATION(), ArgSeq, void, F>
{
  BOOST_MPL_ASSERT_RELATION(boost::mpl::size<ArgSeq>::type::value, ==, BOOST_PP_ITERATION());
  function_constrainer(F f = F()) : f(f) {}
  typedef void result_type;
  void operator()(BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JVB_FUNCTION_CONSTRAINER_repeat_operator, ~)) const
  {
    f(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
  }

  F f;

  F functor() const { return f; }
};

template <typename ArgSeq, typename R, typename F>
struct function_constrainer<BOOST_PP_ITERATION(), ArgSeq, R, F>
{
  BOOST_MPL_ASSERT_RELATION((boost::mpl::size<ArgSeq>::type::value), ==, BOOST_PP_ITERATION());
  function_constrainer(F f = F()) : f(f) {}
  typedef R result_type;
  R operator()(BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JVB_FUNCTION_CONSTRAINER_repeat_operator, ~)) const
  {
    return f(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
  }

  F f;

  F functor() const { return f; }
};
#undef JVB_FUNCTION_CONSTRAINER_repeat_operator

} }

#endif

