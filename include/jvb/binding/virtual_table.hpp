// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_VIRTUAL_TABLE_HPP
#define JVB_BINDING_VIRTUAL_TABLE_HPP

#include <boost/mpl/assert.hpp>

namespace jvb { namespace binding {

struct virtual_method_item
{
  // shared_ptr keeps the destruction function,
  // so this is safe
  boost::shared_ptr<void> function_object;
};

template <std::size_t N>
struct virtual_table
{
  virtual_table() {}
  virtual_table(virtual_table<(N?N-1:0)> const& before)
  {
    BOOST_MPL_ASSERT_RELATION(N, !=, 0);
  }

  virtual_method_item methods[N];
};

} }

#endif
