// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CREATE_CLASS_HPP
#define JVB_CREATE_CLASS_HPP

#include <jvb/function_definition.hpp>

#include <boost/preprocessor/seq/first_n.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/mpl/identity.hpp>

#define JVB_PP_CREATE_CLASS_FILLER_0(X, Y)                                \
    ((X, Y)) JVB_PP_CREATE_CLASS_FILLER_1
#define JVB_PP_CREATE_CLASS_FILLER_1(X, Y)                                \
    ((X, Y)) JVB_PP_CREATE_CLASS_FILLER_0
#define JVB_PP_CREATE_CLASS_FILLER_0_END
#define JVB_PP_CREATE_CLASS_FILLER_1_END

#define JVB_CREATE_CLASS_MEMBER_TERMINAL(NAME, FUNCTION, C)       \
  ::jvb::bind_placeholders::method<typename C::BOOST_PP_CAT(NAME, _definition)> \
  (jvb::bind_placeholders::public_, FUNCTION)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_METHOD_M(R, C, I, METHOD)     \
  BOOST_PP_COMMA_IF(I)                                                  \
  JVB_CREATE_CLASS_MEMBER_TERMINAL(BOOST_PP_TUPLE_ELEM(2, 0, METHOD)    \
                                   , BOOST_PP_TUPLE_ELEM(2, 1, METHOD), C)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS_AUX(METHODS, C)        \
  BOOST_PP_SEQ_FOR_EACH_I(JVB_CREATE_CLASS_MEMBER_DEFINE_METHOD_M, C, METHODS)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS(METHODS, C)        \
  JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS_AUX                      \
  (BOOST_PP_CAT(JVB_PP_CREATE_CLASS_FILLER_0 METHODS, _END), C)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_AUX_NAME_methods \
  JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS(

#define JVB_CREATE_CLASS(C, P, ENV/*, MODIFIERS*/, MEMBERS)     \
  jvb::bind_class<C, P>(ENV,                                    \
                          (BOOST_PP_CAT(JVB_CREATE_CLASS_MEMBER_DEFINE_AUX_NAME_ \
                                        , BOOST_PP_SEQ_ELEM(0, MEMBERS)), C)) \
  );

  

#endif
