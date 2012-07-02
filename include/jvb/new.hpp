// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_NEW_HPP
#define JVB_NEW_HPP

#include <jvb/environment.hpp>
#include <jvb/reference.hpp>
#include <jvb/constructors.hpp>
#include <jvb/detail/new_object_functor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/equal_to.hpp>

namespace jvb {

template <typename R, typename Sig>
R new_(environment e, constructors<Sig> c)
{
  BOOST_MPL_ASSERT((boost::is_same<typename boost::function_types::result_type<Sig>::type, void>));
  BOOST_MPL_ASSERT((boost::mpl::equal_to<boost::function_types::function_arity<Sig>, boost::mpl::size_t<0u> >));

  return detail::new_object_functor<R>()(e, c.class_(), c.raw());
}

}

#endif
