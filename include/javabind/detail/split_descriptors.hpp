// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_SPLIT_DESCRIPTORS_HPP
#define JAVABIND_DETAIL_SPLIT_DESCRIPTORS_HPP

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/if.hpp>

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>

namespace javabind { namespace detail {

template <typename ResultDescriptor>
struct split_descriptors
{
  typedef typename ResultDescriptor::all_primitives all_primitives;

  template <typename S>
  struct my_result
  {
    typedef typename boost::mpl::if_
    <all_primitives
     , std::pair<boost::fusion::vector0<>
                 , S>
     , std::pair<boost::fusion::vector1
                 <typename boost::remove_reference
                  <typename boost::fusion::result_of::deref
                   <typename boost::fusion::result_of::begin
                    <S>::type>::type>::type>
                 , typename boost::fusion::result_of::pop_front<S const>::type
                 > >::type type;
  };

  template <typename S>
  static typename my_result<S>::type split_aux(S const& s, boost::mpl::false_)
  {
    typedef typename my_result<S>::type result_type;
    return result_type(boost::fusion::vector1
                       <typename boost::remove_reference
                        <typename boost::fusion::result_of::deref
                         <typename boost::fusion::result_of::begin
                          <S>::type>::type>::type>
                       (boost::fusion::deref(boost::fusion::begin(s)))
                       , boost::fusion::pop_front(s));
  }

  template <typename S>
  static typename my_result<S>::type split_aux(S const& s, boost::mpl::true_)
  {
    typedef typename my_result<S>::type result_type;
    return result_type(boost::fusion::vector0<>(), s);
  }

  template <typename S>
  static typename my_result<S>::type split(S const& s)
  {
    return split_aux(s, typename all_primitives::type());
  }
};

} }

#endif
