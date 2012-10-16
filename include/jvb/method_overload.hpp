// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING) || !BOOST_PP_IS_ITERATING

#ifndef JVB_METHOD_OVERLOAD_HPP
#define JVB_METHOD_OVERLOAD_HPP

#include <jvb/object.hpp>
#include <jvb/environment.hpp>
#include <jvb/method.hpp>
#include <jvb/detail/overload_set.hpp>
#include <jvb/detail/select_call_functor.hpp>
#include <jvb/detail/descriptors.hpp>
#include <jvb/detail/max_args.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/joint_view.hpp>

#if BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX < JVB_MAX_ARGS
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX JVB_MAX_ARGS
#endif
#include <boost/functional/overloaded_function.hpp>
#include <boost/utility/enable_if.hpp>

#include <iterator>

#include <jni.h>

namespace jvb { namespace detail {

struct method_overload_enabler {};

}

template <typename F>
struct normalize_method_signature
{
  typedef typename boost::function_types::function_type
  <
    typename boost::mpl::joint_view
    <
      boost::mpl::vector2
      <typename boost::function_types::result_type<F>::type, jvb::environment>
      , typename boost::function_types::parameter_types<F>::type
      >::type
  >::type type;
};

#define BOOST_PP_ITERATION_PARAMS_1 (3, (2, JVB_MAX_ARGS, "jvb/method_overload.hpp"))
#include BOOST_PP_ITERATE()

}

#endif
#else
#define JVB_METHOD_OVERLOAD_at_c(z, n, data)                    \
  BOOST_PP_COMMA_IF(n) typename normalize_method_signature      \
  <typename boost::mpl::at_c<Seq, n>::type>::type

#define JVB_METHOD_OVERLOAD_method(z, n, data)                          \
  BOOST_PP_COMMA_IF(n) jvb::method                                      \
  <typename boost::mpl::at_c<Seq, n>::type>(e, obj, name)

template <typename Seq>
boost::overloaded_function
<BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JVB_METHOD_OVERLOAD_at_c, ~)>
method_overload(jvb::environment e, jobject obj, const char* name
                , typename boost::enable_if
                <boost::mpl::equal_to<typename boost::mpl::size<Seq>::type
                , boost::mpl::size_t<BOOST_PP_ITERATION()> >
                , jvb::detail::method_overload_enabler>::type
                = jvb::detail::method_overload_enabler())
{
  typedef boost::overloaded_function
    <BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JVB_METHOD_OVERLOAD_at_c, ~)>
    result_type;
  return result_type
    (BOOST_PP_REPEAT(BOOST_PP_ITERATION(), JVB_METHOD_OVERLOAD_method, ~));
}
#undef JVB_METHOD_OVERLOAD_at_c
#undef JVB_METHOD_OVERLOAD_method
#endif
