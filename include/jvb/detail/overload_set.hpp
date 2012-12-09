// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_OVERLOAD_SET_HPP
#define JVB_DETAIL_OVERLOAD_SET_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/detail/function_constrainer.hpp>
#include <jvb/string.hpp>
#include <jvb/environment.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#include <boost/function_types/parameter_types.hpp>

namespace jvb { namespace detail {

namespace mpl = boost::mpl;

template <typename V, typename E>
struct push_all
{
  struct push_all_in
  {
    template <typename S, typename F>
    struct apply
    {
      typedef typename mpl::push_back
      <S, typename mpl::push_back<F, E>::type>::type type;
    };
  };

  typedef typename mpl::fold
  <V, mpl::vector0<>, push_all_in>::type type;
};

template <typename V>
struct push_string_alternatives
{
  typedef typename push_all<V, jvb::string>::type string_alt;
  typedef typename push_all<V, const char*>::type char_alt;
  typedef mpl::joint_view<string_alt, char_alt> type;
};

struct create_overloads
{
  template <typename State, typename E>
  struct apply
  {
    typedef typename
    mpl::if_<boost::is_same<E, jvb::string>
                    , typename push_string_alternatives<State>::type
                    , typename push_all<State, E>::type
                    >::type type;
  };
};

template <typename ArgSeq>
struct convertible_overloads
  : mpl::fold
    <
    typename mpl::push_front<ArgSeq, environment>::type
    , mpl::vector1<mpl::vector0<> >
    , create_overloads
    >
{
};

template <typename ArgSeq, typename R, typename F>
struct function_set : function_constrainer_group
<mpl::size<typename convertible_overloads<ArgSeq>::type>::type::value
 , typename convertible_overloads<ArgSeq>::type
 , R, F>
{
  typedef function_constrainer_group
  <mpl::size<typename convertible_overloads<ArgSeq>::type>::type::value
   , typename convertible_overloads<ArgSeq>::type
   , R, F> base_type;
  function_set(F f)
    : base_type(f) {}
};

template <typename Sigs>
struct convertible_overloads_for_all
  : mpl::fold
    <
     Sigs
     , mpl::vector0<>
     , mpl::joint_view
     <
       mpl::_1
       , convertible_overloads<boost::function_types::parameter_types<mpl::_2> >
     >
    >
{
};

template <typename Sigs, typename R, typename F>
struct overload_set : function_constrainer_group
<mpl::size<typename convertible_overloads_for_all<Sigs>::type>::type::value
 , typename convertible_overloads_for_all<Sigs>::type
 , R, F>
{
  typedef function_constrainer_group
<mpl::size<typename convertible_overloads_for_all<Sigs>::type>::type::value
 , typename convertible_overloads_for_all<Sigs>::type
 , R, F> base_type;
  overload_set(F f)
    : base_type(f) {}
};

} }

#endif
