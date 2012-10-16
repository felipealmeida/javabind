// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_IMPLEMENTS_HPP
#define JVB_IMPLEMENTS_HPP

#include <boost/preprocessor/repetition/enum_params.hpp>

#include <jvb/detail/max_args.hpp>

namespace jvb {

template <BOOST_PP_ENUM_PARAMS(JVB_MAX_ARGS, typename T)>
struct implements
{
  
};

}

#endif
