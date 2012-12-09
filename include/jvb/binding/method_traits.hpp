// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING) || !BOOST_PP_IS_ITERATING

#ifndef JVB_BINDING_METHOD_TRAITS_HPP
#define JVB_BINDING_METHOD_TRAITS_HPP

#include <jvb/environment.hpp>
#include <jvb/detail/max_args.hpp>

#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/mem_fn.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/identity.hpp>

namespace jvb { namespace binding {

namespace mpl = boost::mpl;

template <typename F, typename P>
struct method_traits
{
  struct void_ { typedef void_ type; };

  typedef typename boost::function_types::result_type<F>::type result_type;
  typedef typename boost::function_types::is_member_function_pointer<F>::type is_member_function_pointer;
  typedef typename boost::function_types::parameter_types<F>::type parameter_types;
  typedef typename mpl::empty<parameter_types>::type empty_parameter_types;

  typedef typename mpl::if_
    <is_member_function_pointer
     , typename mpl::at_c<parameter_types, 0u>::type
     , void_>::type member_class_type;

  typedef typename boost::remove_cv
  <typename boost::remove_reference<
     typename mpl::eval_if_c
     <(boost::mpl::size<parameter_types>::value >= 1)
      , boost::mpl::at_c<parameter_types, 0>
      , void_
      >::type>::type>::type arg0_type;
  
  typedef  typename boost::remove_cv
  <typename boost::remove_reference<
     typename mpl::eval_if_c
     <(boost::mpl::size<parameter_types>::value >= 2)
     , boost::mpl::at_c<parameter_types, 1>
     , void_
     >::type>::type>::type arg1_type;

  // typedef typename mpl::eval_if_c
  // <boost::mpl::size<parameter_types>::value >= 3
  //  , void_
  //  , boost::mpl::at_c<parameter_types, 2>
  // >::type arg2_type;

  // Peer class type: 
  //     ((arg0_type != void_ /\ arg0_type != environment) \/ is_member_function_pointer
  //      => peer_class = arg0_type)

  // has_environment:
  // has_environment = (arg1_type = environment \/ arg0_type = environment)

  typedef typename boost::mpl::or_
  <
    boost::is_same<arg0_type, environment>
    , boost::is_same<arg1_type, environment>
  >::type has_environment;

  // BOOST_MPL_ASSERT((mpl::or_<boost::is_same<arg0_type, environment>
  //                   , boost::is_same<arg1_type, environment> >));


  typedef typename boost::mpl::if_
  <
    mpl::or_
    <
      is_member_function_pointer
    , mpl::not_
      <
        mpl::or_
        <
          boost::is_same<arg0_type, void_>
        , boost::is_same<arg0_type, environment>
        >
      >
    >
    , arg0_type
    , void_
  >::type peer_class_type;

  typedef typename mpl::not_<boost::is_same<void_, peer_class_type> >::type has_peer_class;

  typedef typename mpl::eval_if
  <has_peer_class
   , mpl::pop_front<parameter_types>
   , mpl::identity<parameter_types>
   >::type removed_peer_parameters;

  typedef typename mpl::eval_if
  <has_environment
   , mpl::pop_front<removed_peer_parameters>
   , mpl::identity<removed_peer_parameters>
   >::type removed_environment_parameters;

  typedef mpl::joint_view
  < mpl::vector3<result_type, jvb::environment, jvb::Object>
    , removed_environment_parameters
  > binding_types;
  typedef typename boost::function_types::function_type<binding_types>::type binding_signature;

  typedef mpl::joint_view
  < mpl::vector3<result_type, P&, jvb::environment>
    , removed_environment_parameters
  > caller_types;
  typedef typename boost::function_types::function_type<caller_types>::type caller_signature;

  template <typename Func>
  struct function_caller
  {
    function_caller(Func f)
      : f(f) {}

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, JVB_MAX_ARGS, "jvb/binding/method_traits.hpp"))
#include BOOST_PP_ITERATE()

    Func f;
  };
};

} }
#endif
#else
template <typename FF, typename PeerClass 
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
static result_type call_aux(FF f, PeerClass& peer, environment e
                            , boost::mpl::false_, boost::mpl::false_
                            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return f(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename FF, typename PeerClass 
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
static result_type call_aux(FF f, PeerClass& peer, environment e
                            , boost::mpl::false_, boost::mpl::true_
                            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return f(e BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename FF, typename PeerClass 
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
static result_type call_aux(FF f, PeerClass& peer, environment e
                            , boost::mpl::true_, boost::mpl::false_
                            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return f(peer BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename FF, typename PeerClass 
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
static result_type call_aux(FF f, PeerClass& peer, environment e
                            , boost::mpl::true_, boost::mpl::true_
                            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return f(peer, e BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename FF, typename PeerClass, typename B1, typename B2
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
static result_type call_aux1(FF f, PeerClass& peer, environment e
                             , B1 b1, B2 b2
                             , boost::mpl::true_
                             BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return call_aux(boost::mem_fn(f), peer, e, b1, b2
                  BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename FF, typename PeerClass, typename B1, typename B2
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
static result_type call_aux1(FF f, PeerClass& peer, environment e
                             , B1 b1, B2 b2
                             , boost::mpl::false_
                             BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return call_aux(f, peer, e, b1, b2 BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename PeerClass 
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
result_type operator()(PeerClass& peer, environment e
                       BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return call_aux1(f, peer, e, has_peer_class(), has_environment()
                   , is_member_function_pointer()
                   BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}
#endif
