// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_PEER_INFO_HPP
#define JVB_BINDING_PEER_INFO_HPP

#include <jvb/binding/virtual_table.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>

namespace jvb { namespace binding {

template <typename P, std::size_t N>
struct peer_info
{
  peer_info(virtual_table<N>const& vtable, P p)
    : vtable(vtable), peer(p)
  {}

  peer_info(virtual_table<N>const& vtable, boost::shared_ptr<P> p)
    : vtable(vtable), peer(p)
  {}

  virtual_table<N>const& vtable;
  boost::variant<boost::shared_ptr<P>, P> peer;
};

} }

#endif
