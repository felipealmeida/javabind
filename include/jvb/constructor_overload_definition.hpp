// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#ifndef JVB_CONSTRUCTOR_OVERLOAD_DEFINITION_HPP
#define JVB_CONSTRUCTOR_OVERLOAD_DEFINITION_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/function_constrainer.hpp>
#include <jvb/detail/new_object_functor.hpp>
#include <jvb/environment.hpp>
#include <jvb/constructors.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_type.hpp>

namespace jvb {

namespace mpl = boost::mpl;

template <typename R>
struct constructor_overload_definition_object
{
  typedef R result_type;

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, JVB_MAX_ARGS, "jvb/constructor_overload_definition.hpp"))
#include BOOST_PP_ITERATE()

};

}

#endif
#else

#if BOOST_PP_ITERATION() != 0
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
#endif
result_type operator()(environment e
                       BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  typedef mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)> param_types;
  typedef typename mpl::transform
    <param_types
     , mpl::if_
     <boost::is_same<mpl::_1, const char*>
      , jvb::string
      , mpl::_1> >::type correct_param_types;
  typedef typename boost::function_types::function_type
    <typename mpl::push_front<correct_param_types, result_type>::type>::type
    sig_type;
  Class cls(e, R::name());
  assert(cls.raw() != 0);
  constructors<sig_type> m(e, cls);
  assert(m.raw() != 0);
  detail::new_object_functor<result_type> c;
  return c(e, cls, m.raw() BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

#endif
