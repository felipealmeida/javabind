// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CREATE_CLASS_HPP
#define JVB_CREATE_CLASS_HPP

#include <jvb/function_definition.hpp>
#include <jvb/bind_class.hpp>
#include <jvb/detail/preprocessor/seq_filler.hpp>

#include <boost/fusion/include/make_vector.hpp>

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

#define JVB_CREATE_CLASS_MEMBER_DEFINE_METHOD_DEF(NAME, FUNCTION, C)       \
  ::jvb::binding::method<C::BOOST_PP_CAT(NAME, _definition)> \
  (jvb::binding::public_, FUNCTION)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_METHOD_M(R, C, I, METHOD)        \
  BOOST_PP_COMMA_IF(I)                                                  \
  JVB_CREATE_CLASS_MEMBER_DEFINE_METHOD_DEF(BOOST_PP_TUPLE_ELEM(2, 0, METHOD) \
                                            , BOOST_PP_TUPLE_ELEM(2, 1, METHOD), C)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH(METHODS, C, P, ENV) \
  ::boost::fusion::make_vector(BOOST_PP_SEQ_FOR_EACH_I(JVB_CREATE_CLASS_MEMBER_DEFINE_METHOD_M, C, METHODS))

#define JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS(METHODS, C, P, ENV)       \
  JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH(BOOST_PP_CAT(JVB_PP_SEQ_FILLER_2_0 METHODS, _END), C, P, ENV)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTOR_DEF(SIG, FUNCTION, C) \
  ::jvb::binding::factory_constructor<SIG> \
  (jvb::binding::public_, FUNCTION)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTOR_M(R, C, I, METHOD)        \
  BOOST_PP_COMMA_IF(I)                                                  \
  JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTOR_DEF(BOOST_PP_TUPLE_ELEM(2, 0, METHOD) \
                                                         , BOOST_PP_TUPLE_ELEM(2, 1, METHOD), C)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTORS_FOR_EACH(METHODS, C, P, ENV) \
  ::boost::fusion::make_vector(BOOST_PP_SEQ_FOR_EACH_I(JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTOR_M, C, METHODS))

#define JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTORS(CONSTRUCTORS, C, P, ENV) \
  JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTORS_FOR_EACH(BOOST_PP_CAT(JVB_PP_SEQ_FILLER_2_0 CONSTRUCTORS, _END), C, P, ENV)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_ALLOCATOR(ALLOCATOR, C, P, ENV) \
  ::jvb::binding::allocator(ALLOCATOR)

#define JVB_CREATE_CLASS_MEMBER_DEFINE_AUX_NAME_methods \
  JVB_CREATE_CLASS_MEMBER_DEFINE_METHODS BOOST_PP_LPAREN()

#define JVB_CREATE_CLASS_MEMBER_DEFINE_AUX_NAME_factory_constructors \
  JVB_CREATE_CLASS_MEMBER_DEFINE_FACTORY_CONSTRUCTORS BOOST_PP_LPAREN()

#define JVB_CREATE_CLASS_MEMBER_DEFINE_AUX_NAME_allocator \
  JVB_CREATE_CLASS_MEMBER_DEFINE_allocator BOOST_PP_LPAREN()

#define JVB_CREATE_CLASS_NO_EXPAND_MEMBER_EAT(M, C, P, ENV)     \
   ::boost::mpl::void_()

#define JVB_CREATE_CLASS_NO_EXPAND_MEMBER(I, MEMBERS)  \
  JVB_CREATE_CLASS_NO_EXPAND_MEMBER_EAT BOOST_PP_LPAREN() ~

#define JVB_CREATE_CLASS_EXPAND_MEMBER(I, MEMBERS)                      \
  BOOST_PP_CAT(JVB_CREATE_CLASS_MEMBER_DEFINE_AUX_NAME_                 \
               , BOOST_PP_SEQ_ELEM(I, MEMBERS )) 

#define JVB_CREATE_CLASS(C, P, ENV/*, MODIFIERS*/, MEMBERS)             \
  jvb::bind_class<C, P>(ENV,                                            \
    BOOST_PP_EXPAND                                                     \
    (JVB_CREATE_CLASS_EXPAND_MEMBER(0, MEMBERS)                         \
     BOOST_PP_COMMA() C BOOST_PP_COMMA() P BOOST_PP_COMMA() ENV BOOST_PP_RPAREN() \
      )                                                                 \
  , BOOST_PP_EXPAND                                \
      (BOOST_PP_IIF                                                     \
      (BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(MEMBERS), 1)                  \
       , JVB_CREATE_CLASS_EXPAND_MEMBER                                 \
       , JVB_CREATE_CLASS_NO_EXPAND_MEMBER)                             \
       (1, MEMBERS)                                                     \
       BOOST_PP_COMMA() C BOOST_PP_COMMA() P BOOST_PP_COMMA() ENV       \
       BOOST_PP_RPAREN())                                               \
  , BOOST_PP_EXPAND                                                     \
      (BOOST_PP_IIF                                                     \
      (BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(MEMBERS), 2)                  \
       , JVB_CREATE_CLASS_EXPAND_MEMBER                                 \
       , JVB_CREATE_CLASS_NO_EXPAND_MEMBER)                             \
       (2, MEMBERS)                                                     \
       BOOST_PP_COMMA() C BOOST_PP_COMMA() P BOOST_PP_COMMA() ENV       \
       BOOST_PP_RPAREN())                                               \
    );

#endif
