// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_OVERLOAD_MATCHES_HPP
#define JVB_DETAIL_OVERLOAD_MATCHES_HPP

#include <boost/function_types/parameter_types.hpp>

namespace jvb { namespace detail {

namespace mpl = boost::mpl;

template <typename F, typename N>
struct is_parameter_size_equal_to
{
  typedef typename boost::function_types::parameter_types<F>::type parameter_types;
  // BOOST_MPL_ASSERT((boost::is_same<typename mpl::size<parameter_types>::type, void>));
  typedef typename mpl::equal_to<typename mpl::size<parameter_types>::type, N>::type type;
};

} }

#endif
