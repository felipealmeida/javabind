// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_CLASS_HPP
#define JVB_ADAPT_CLASS_HPP

#include <jvb/function_definition.hpp>
#include <jvb/field.hpp>
#include <jvb/detail/preprocessor/seq_filler.hpp>

#include <boost/preprocessor/seq/first_n.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>

#include <boost/mpl/identity.hpp>

#define JVB_ADAPT_CLASS_DEFINE_methods(r, data, elem)

#define JVB_ADAPT_CLASS_MEMBER_FLATTEN_methods_aux(methods) methods

#define JVB_ADAPT_CLASS_MEMBER_FLATTEN_attributes_aux(attributes) attributes

#define JVB_ADAPT_CLASS_MEMBER_FLATTEN_NAME_methods   \
  JVB_ADAPT_CLASS_MEMBER_FLATTEN_methods_aux(

#define JVB_ADAPT_CLASS_MEMBER_FLATTEN_NAME_attributes   \
  JVB_ADAPT_CLASS_MEMBER_FLATTEN_attributes_aux(

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHOD(NAME, SIGNATURE)          \
  struct BOOST_PP_CAT(NAME, _definition)                                \
    : ::jvb::function_definition<BOOST_PP_CAT(NAME, _definition)        \
                                 , SIGNATURE, self_type>                \
  {                                                                     \
    typedef ::jvb::function_definition<BOOST_PP_CAT(NAME, _definition)  \
                                       , SIGNATURE, self_type> aux_type; \
    BOOST_PP_CAT(NAME, _definition)(jobject obj)                        \
      : aux_type(obj) {}                                                \
    typedef self_type this_type;                                        \
    typedef boost::mpl::identity<SIGNATURE>::type sig_type;             \
    static const std::size_t name_size = sizeof(BOOST_PP_STRINGIZE(NAME))-1; \
    static const char* name()                                           \
    {                                                                   \
      return BOOST_PP_STRINGIZE(NAME);                                  \
    }                                                                   \
  };                                                                    \
  BOOST_PP_CAT(NAME, _definition) NAME() const                          \
  {                                                                     \
    return BOOST_PP_CAT(NAME, _definition)(raw());                       \
  }

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHOD_M(r, data, elem) \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_METHOD                        \
  (BOOST_PP_TUPLE_ELEM(2, 0, elem), BOOST_PP_TUPLE_ELEM(2, 1, elem))

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_SEQ_M(r, data, I, ELEM)    \
  BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, ELEM), _definition)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH(METHODS)        \
  BOOST_PP_SEQ_FOR_EACH(JVB_ADAPT_CLASS_MEMBER_DEFINE_METHOD_M, ~, METHODS) \
  boost::mpl::vector                                                    \
  <BOOST_PP_SEQ_FOR_EACH_I                                              \
   (JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_SEQ_M, ~, METHODS)> all_methods;

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTE(NAME, TYPE)     \
  struct BOOST_PP_CAT(NAME, _definition)                        \
  {                                                             \
    BOOST_PP_CAT(NAME, _definition)( ::jvb::environment e, jobject obj) \
      : e(e), obj(obj) {}                                               \
                                                                        \
    operator TYPE() const                                               \
    {                                                                   \
      return ::jvb::read_field<self_type, TYPE>(e, obj, name());        \
    }                                                                   \
    bool operator==(TYPE other) const                                   \
    {                                                                   \
      TYPE self = *this;                                                \
      return self == other;                                             \
    }                                                                   \
    BOOST_PP_CAT(NAME, _definition) const& operator=(TYPE x) const      \
    {                                                                 \
      ::jvb::write_field<self_type>(e, obj, name(), x);                 \
      return *this;                                                     \
    }                                                                   \
    static const std::size_t name_size = sizeof(BOOST_PP_STRINGIZE(NAME))-1; \
    static const char* name()                                           \
    {                                                                   \
      return BOOST_PP_STRINGIZE(NAME);                                  \
    }                                                                   \
    ::jvb::environment e;                                               \
    jobject obj;                                                        \
  };                                                            \
  BOOST_PP_CAT(NAME, _definition) NAME( ::jvb::environment e) const     \
  {                                                             \
    return BOOST_PP_CAT(NAME, _definition) (e, raw());          \
  }

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTE_M(R, DATA, ATTRIBUTE)   \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTE ATTRIBUTE

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES_FOR_EACH(ATTRIBUTES) \
  BOOST_PP_SEQ_FOR_EACH(JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTE_M, ~, ATTRIBUTES)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS(METHODS)                 \
  JVB_PP_CALL_FILLED(JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH, METHODS)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES(ATTRIBUTES)            \
  JVB_PP_CALL_FILLED(JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES_FOR_EACH, ATTRIBUTES)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_methods \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_attributes \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS_NAME(c)                \
  BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(c)), c)

#define JVB_ADAPT_CLASS_PACKAGE_M(R, DATA, I, E)       \
  BOOST_PP_EXPR_IF(I, "/") BOOST_PP_STRINGIZE(E)

#define JVB_ADAPT_CLASS_PACKAGE_AND_NAME_STRING(c)                             \
  BOOST_PP_SEQ_FOR_EACH_I(JVB_ADAPT_CLASS_PACKAGE_M, ~, c)

#define JVB_ADAPT_CLASS_EXPAND_MEMBER(I, MEMBERS)                      \
    BOOST_PP_CAT(JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_               \
                 , BOOST_PP_SEQ_ELEM(I, MEMBERS )) 

#define JVB_ADAPT_CLASS_NO_EXPAND_MEMBER(I, MEMBERS)    \
  BOOST_PP_EMPTY BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS(C, modifiers, MEMBERS)                         \
  struct JVB_ADAPT_CLASS_NAME(C) : jvb::object                         \
  {                                                                     \
    typedef JVB_ADAPT_CLASS_NAME(C) self_type;                         \
    typedef jvb::object base_type;                                      \
    JVB_ADAPT_CLASS_NAME(C) ( ::jvb::environment e, ::jobject o)       \
      : base_type(e, o) {}                                              \
    BOOST_PP_EXPAND                                                     \
      (JVB_ADAPT_CLASS_EXPAND_MEMBER(0, MEMBERS) BOOST_PP_RPAREN()      \
       )                                                               \
    BOOST_PP_EXPAND                                                     \
      (BOOST_PP_IIF                                                     \
      (BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(MEMBERS), 1)                  \
       , JVB_ADAPT_CLASS_EXPAND_MEMBER, JVB_ADAPT_CLASS_NO_EXPAND_MEMBER) \
       (1, MEMBERS) BOOST_PP_RPAREN())                                  \
    BOOST_PP_EXPAND                                                     \
      (BOOST_PP_IIF                                                     \
      (BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(MEMBERS), 2)                  \
       , JVB_ADAPT_CLASS_EXPAND_MEMBER, JVB_ADAPT_CLASS_NO_EXPAND_MEMBER) \
       (2, MEMBERS) BOOST_PP_RPAREN())                                  \
    BOOST_PP_EXPAND                                                     \
      (BOOST_PP_IIF                                                     \
      (BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(MEMBERS), 3)                  \
       , JVB_ADAPT_CLASS_EXPAND_MEMBER, JVB_ADAPT_CLASS_NO_EXPAND_MEMBER) \
       (3, MEMBERS) BOOST_PP_RPAREN())                                  \
    static const std::size_t name_size =                                \
      sizeof(JVB_ADAPT_CLASS_PACKAGE_AND_NAME_STRING(C)) - 1;          \
    static const char* name()                                           \
    {                                                                   \
      return JVB_ADAPT_CLASS_PACKAGE_AND_NAME_STRING(C);               \
    }                                                                   \
  };



#endif
