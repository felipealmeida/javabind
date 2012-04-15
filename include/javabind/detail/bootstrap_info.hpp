// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_BOOTSTRAP_INFO_HPP
#define JAVABIND_DETAIL_BOOTSTRAP_INFO_HPP

#include <javabind/detail/bootstrap_info.hpp>
#include <javabind/reg/class.hpp>
#include <javabind/reg/constructor.hpp>
#include <javabind/field.hpp>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>

#include <boost/fusion/algorithm/iteration/fold.hpp>

#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>

#include <boost/type_traits/remove_reference.hpp>

namespace javabind { namespace detail {

struct bootstrap_info
{
  bootstrap_info(field<jlong> peer, std::size_t n)
    : peer(peer), vtable(n) {}
  field<jlong> peer;
  std::vector<void const*> vtable;
};

struct initialize_vtable
{
  initialize_vtable(std::vector<void const*>& vtable)
  : vtable(vtable) {}

  template <typename T>
  struct result
  {
    typedef typename boost::mpl::deref
    <typename boost::mpl::begin
     <typename boost::function_types::parameter_types<T>::type>::type>::type first_type;
    typedef typename boost::remove_reference<first_type>::type increment_type;
    typedef boost::mpl::size_t<increment_type::type::value+1> type;
  };

  template <std::size_t N, typename FEntry>
  boost::mpl::size_t<N+1> operator()(boost::mpl::size_t<N>, FEntry const& entry) const
  {
    std::cout << "Initializing vtable[" << N << "] with " << &entry.f << std::endl;
    vtable[N] = &entry.f;
    return boost::mpl::size_t<N+1>();
  }

  std::vector<void const*>& vtable;
};

template <typename S, typename C>
struct bootstrap_info_derived : bootstrap_info
{
  typedef bootstrap_info base_type;
  bootstrap_info_derived(S s, field<jlong> peer, C c)
    :  base_type(peer, boost::fusion::result_of::size<S>::type::value), s(s), c(c)
  {
    boost::fusion::fold(this->s, boost::mpl::size_t<0u>(), initialize_vtable(this->vtable));
  }
  S s;
  C c;
};

template <typename S, typename C>
struct bootstrap_info_derived_with_extends : bootstrap_info_derived<S, C>
{
  typedef bootstrap_info_derived<S, C> base_type;
  bootstrap_info_derived_with_extends(S s, field<jlong> peer, C c
                                      , field<jlong> extends_peer)
    :  base_type(s, peer, c), extends_peer(extends_peer)
  {
  }

  field<jlong> extends_peer;
};


} }

#endif
