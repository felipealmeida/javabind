// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef JAVABIND_DESCRIPTOR_HPP
#define JAVABIND_DESCRIPTOR_HPP

#include <javabind/detail/max_args.hpp>

#include <boost/fusion/container/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, JAVABIND_MAX_ARGS, "javabind/descriptors.hpp"))
#include BOOST_PP_ITERATE ()

#endif
#else

namespace javabind {

template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
BOOST_PP_CAT(boost::fusion::vector, BOOST_PP_ITERATION())
<BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)>
descriptors(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return BOOST_PP_CAT(boost::fusion::vector, BOOST_PP_ITERATION())
    <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)>
    (BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
}

}

#endif
