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
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/begin.hpp>

#if BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX < BOOST_PP_INC(JVB_MAX_ARGS)
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX BOOST_PP_INC(JVB_MAX_ARGS)
#endif
#include <boost/functional/overloaded_function.hpp>
#include <boost/utility/enable_if.hpp>

#include <iterator>

#include <jni.h>

namespace jvb { namespace detail {

template <typename F>
struct add_environment
{
  typedef typename boost::function_types::function_type
  <boost::mpl::joint_view
   <boost::mpl::vector2
    <typename boost::function_types::result_type
     <F>::type, jvb::environment>
    ,typename boost::function_types::parameter_types
    <F>::type
    > >::type type;
};

}

#define JVB_METHOD_OVERLOAD_overload(n) BOOST_PP_CAT(F, n)
#define JVB_METHOD_OVERLOAD_add_environment(n)  \
  typename boost::mpl::eval_if                                          \
  <boost::is_same<void, JVB_METHOD_OVERLOAD_overload(n)>                \
   , boost::mpl::identity<void>                                         \
   , jvb::detail::add_environment<JVB_METHOD_OVERLOAD_overload(n)>      \
   >::type

#define JVB_METHOD_OVERLOAD_enum_overload(z, n, data)   \
  JVB_METHOD_OVERLOAD_add_environment(n)

template <int N BOOST_PP_ENUM_TRAILING_PARAMS(JVB_MAX_ARGS, typename F)>
struct method_overload_aux
  : boost::overloaded_function
     <BOOST_PP_ENUM(JVB_MAX_ARGS, JVB_METHOD_OVERLOAD_enum_overload, ~)>
{
  typedef boost::overloaded_function
  <BOOST_PP_ENUM(JVB_MAX_ARGS, JVB_METHOD_OVERLOAD_enum_overload, ~)> base_type;
#define BOOST_PP_ITERATION_PARAMS_1 (3, (2, JVB_MAX_ARGS, "jvb/method_overload.hpp"))
#include BOOST_PP_ITERATE()
};

#undef JVB_METHOD_OVERLOAD_add_environment
#undef JVB_METHOD_OVERLOAD_overload

template <BOOST_PP_ENUM_BINARY_PARAMS(JVB_MAX_ARGS, typename F, = void BOOST_PP_INTERCEPT)>
struct method_overload
  : method_overload_aux<boost::mpl::distance
                        <typename boost::mpl::begin
                         <boost::mpl::vector<BOOST_PP_ENUM_PARAMS(JVB_MAX_ARGS, F)> >::type
                         , typename boost::mpl::find
                         <boost::mpl::vector<BOOST_PP_ENUM_PARAMS(JVB_MAX_ARGS, F)>
                         , void>::type
                         >::value
                        BOOST_PP_ENUM_TRAILING_PARAMS(JVB_MAX_ARGS, F)>
{
  typedef boost::mpl::vector<BOOST_PP_ENUM_PARAMS(JVB_MAX_ARGS, F)> params_type;
  typedef typename boost::mpl::distance
  <typename boost::mpl::begin
   <params_type>::type
   , typename boost::mpl::find
   <params_type, void>::type
   >::type params_num;
  typedef method_overload_aux<params_num::value
                              BOOST_PP_ENUM_TRAILING_PARAMS(JVB_MAX_ARGS, F)>
  base_type;

  BOOST_MPL_ASSERT((boost::mpl::not_<boost::is_same<F0, void> >));
  BOOST_MPL_ASSERT((boost::mpl::not_<boost::is_same<F1, void> >));

  method_overload(jvb::environment env, jobject obj, const char* name)
    : base_type(env, obj, name, boost::mpl::size_t<params_num::value>())
  {}
};


}

#endif
#else

#define JVB_METHOD_OVERLOAD_overload_constructor(z, n, data)    \
  jvb::method                                                   \
  <JVB_METHOD_OVERLOAD_overload(n)>(env, obj, name)

method_overload_aux(jvb::environment env, jobject obj, const char* name
                    , boost::mpl::size_t<BOOST_PP_ITERATION()>)
  : base_type(
              BOOST_PP_ENUM(BOOST_PP_ITERATION()
                            , JVB_METHOD_OVERLOAD_overload_constructor, ~)
              )
{
}

#undef JVB_METHOD_OVERLOAD_overload_constructor
#endif
