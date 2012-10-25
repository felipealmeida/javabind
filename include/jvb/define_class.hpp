// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DEFINE_CLASS_HPP
#define JVB_DEFINE_CLASS_HPP

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

#define JVB_PP_DEFINE_CLASS_FILLER_0(X, Y)                                \
    ((X, Y)) JVB_PP_DEFINE_CLASS_FILLER_1
#define JVB_PP_DEFINE_CLASS_FILLER_1(X, Y)                                \
    ((X, Y)) JVB_PP_DEFINE_CLASS_FILLER_0
#define JVB_PP_DEFINE_CLASS_FILLER_0_END
#define JVB_PP_DEFINE_CLASS_FILLER_1_END

#define JVB_DEFINE_CLASS_open_namespace(r, data, elem) namespace elem {
#define JVB_DEFINE_CLASS_close_namespace(r, data, elem) }

#define JVB_DEFINE_CLASS_namespace_expr(c, macro)                       \
  BOOST_PP_EXPR_IF                                                      \
  (BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(c))                                   \
   , BOOST_PP_SEQ_FOR_EACH                                              \
   (macro, ~                                                            \
    , BOOST_PP_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(c)), c)))

#define JVB_DEFINE_CLASS_DEFINE_methods(r, data, elem)

#define JVB_DEFINE_CLASS_MEMBER_FLATTEN_methods_aux(methods) methods

#define JVB_DEFINE_CLASS_MEMBER_FLATTEN_attributes_aux(attributes) attributes

#define JVB_DEFINE_CLASS_MEMBER_FLATTEN_NAME_methods   \
  JVB_DEFINE_CLASS_MEMBER_FLATTEN_methods_aux(

#define JVB_DEFINE_CLASS_MEMBER_FLATTEN_NAME_attributes   \
  JVB_DEFINE_CLASS_MEMBER_FLATTEN_attributes_aux(

#define JVB_DEFINE_CLASS_MEMBER_DEFINE_METHOD(NAME, SIGNATURE)          \
  struct BOOST_PP_CAT(NAME, _definition)                                \
    : ::jvb::function_definition<BOOST_PP_CAT(NAME, _definition)        \
                                 , SIGNATURE, self_type>                \
  {                                                                     \
    typedef self_type this_type;                                        \
    typedef boost::mpl::identity<SIGNATURE>::type sig_type;             \
    static const std::size_t name_size = sizeof(BOOST_PP_STRINGIZE(NAME))-1; \
    static const char* name()                                           \
    {                                                                   \
      return BOOST_PP_STRINGIZE(NAME);                                  \
    }                                                                   \
  };                                                                    \
  BOOST_PP_CAT(NAME, _definition) NAME;

#define JVB_DEFINE_CLASS_MEMBER_DEFINE_METHOD_M(r, data, elem) \
  JVB_DEFINE_CLASS_MEMBER_DEFINE_METHOD                        \
  (BOOST_PP_TUPLE_ELEM(2, 0, elem), BOOST_PP_TUPLE_ELEM(2, 1, elem))

#define JVB_DEFINE_CLASS_MEMBER_DEFINE_METHODS_SEQ_M(r, data, I, ELEM)    \
  BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, ELEM), _definition)

#define JVB_DEFINE_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH(METHODS)        \
  BOOST_PP_SEQ_FOR_EACH(JVB_DEFINE_CLASS_MEMBER_DEFINE_METHOD_M, ~, METHODS) \
  boost::mpl::vector                                                    \
  <BOOST_PP_SEQ_FOR_EACH_I                                              \
   (JVB_DEFINE_CLASS_MEMBER_DEFINE_METHODS_SEQ_M, ~, METHODS)> all_methods;

#define JVB_DEFINE_CLASS_MEMBER_DEFINE_METHODS(METHODS)                 \
  JVB_DEFINE_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH                       \
  (BOOST_PP_CAT(JVB_PP_DEFINE_CLASS_FILLER_0 METHODS,_END))

#define JVB_DEFINE_CLASS_MEMBER_DEFINE_AUX_NAME_methods \
  JVB_DEFINE_CLASS_MEMBER_DEFINE_METHODS(

#define JVB_DEFINE_CLASS_NAME(c)                \
  BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(c)), c)

#define JVB_DEFINE_CLASS_PACKAGE_M(R, DATA, I, E)       \
  BOOST_PP_EXPR_IF(I, "/") BOOST_PP_STRINGIZE(E)

#define JVB_DEFINE_CLASS_PACKAGE_AND_NAME_STRING(c)                             \
  BOOST_PP_SEQ_FOR_EACH_I(JVB_DEFINE_CLASS_PACKAGE_M, ~, c)

#define JVB_DEFINE_CLASS(c, modifiers, MEMBERS)                         \
  struct JVB_DEFINE_CLASS_NAME(c) : jvb::object                         \
  {                                                                     \
    typedef JVB_DEFINE_CLASS_NAME(c) self_type;                         \
    typedef jvb::object base_type;                                      \
    JVB_DEFINE_CLASS_NAME(c) ( ::jvb::environment e, ::jobject o)       \
      : base_type(e, o) {}                                              \
    BOOST_PP_CAT(JVB_DEFINE_CLASS_MEMBER_DEFINE_AUX_NAME_               \
                 , BOOST_PP_SEQ_ELEM(0, MEMBERS)))                      \
    static const std::size_t name_size =                                \
      sizeof(JVB_DEFINE_CLASS_PACKAGE_AND_NAME_STRING(c)) - 1;          \
    static const char* name()                                           \
    {                                                                   \
      return JVB_DEFINE_CLASS_PACKAGE_AND_NAME_STRING(c);               \
    }                                                                   \
  };

#endif
