// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_PREPROCESSOR_SEQUENCE_FILLER_HPP
#define JVB_DETAIL_PREPROCESSOR_SEQUENCE_FILLER_HPP

#include <boost/preprocessor/cat.hpp>

#define JVB_PP_SEQ_FILLER_0(X, Y) ((X, Y)) JVB_PP_SEQ_FILLER_1
#define JVB_PP_SEQ_FILLER_1(X, Y) ((X, Y)) JVB_PP_SEQ_FILLER_0
#define JVB_PP_SEQ_FILLER_0_END
#define JVB_PP_SEQ_FILLER_1_END

#define JVB_PP_CALL_FILLED(MACRO, SEQ) \
  MACRO (BOOST_PP_CAT(JVB_PP_SEQ_FILLER_0 SEQ,_END))

#endif
