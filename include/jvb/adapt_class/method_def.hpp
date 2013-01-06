// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_CLASS_METHOD_DEF_HPP
#define JVB_ADAPT_CLASS_METHOD_DEF_HPP

#include <jvb/adapt_class/modifiers.hpp>
#include <jvb/function_definition.hpp>
#include <jvb/function_static_definition.hpp>

#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/seq/filter.hpp>

#define JVB_ADAPT_CLASS_METHOD_DEF_CHECK_STATIC(NAME, TYPE, MODIFIERS) \
  BOOST_PP_IF(BOOST_PP_IS_EMPTY                                         \
              (JVB_ADAPT_CLASS_HAS_STATIC(JVB_ADAPT_CLASS_MODIFIERS_SEQ(MODIFIERS))) \
                , JVB_ADAPT_CLASS_METHOD_DEF_NO_STATIC               \
              , JVB_ADAPT_CLASS_METHOD_DEF_STATIC)(NAME, TYPE, MODIFIERS)

#define JVB_ADAPT_CLASS_METHOD_DEF(NAME, TYPE, MODIFIERS)            \
  BOOST_PP_IF(BOOST_PP_IS_EMPTY                                         \
              (BOOST_PP_CAT(JVB_ADAPT_CLASS_METHOD_DEF_CONSUME_IF_NIL_, MODIFIERS)) \
              , JVB_ADAPT_CLASS_METHOD_DEF_NO_STATIC                    \
              , JVB_ADAPT_CLASS_METHOD_DEF_CHECK_STATIC)(NAME,  ::jvb::signatures::convert_signature<TYPE>::type, MODIFIERS)

#define JVB_ADAPT_CLASS_METHOD_DEF_NO_STATIC(NAME, SIGNATURE, MODIFIERS) \
  struct BOOST_PP_CAT(NAME, _definition)                                \
    : ::jvb::detail::function_set                                       \
  <                                                                     \
   boost::function_types::parameter_types< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type \
   , boost::function_types::result_type< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type \
   , ::jvb::function_definition_object                                  \
   <BOOST_PP_CAT(NAME, _definition),  ::jvb::signatures::convert_signature<SIGNATURE>::type, self_type> > \
  {                                                                     \
    typedef ::jvb::detail::function_set                                 \
      <                                                                 \
       boost::function_types::parameter_types< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type \
       , boost::function_types::result_type< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type \
       , ::jvb::function_definition_object                              \
       <BOOST_PP_CAT(NAME, _definition),  ::jvb::signatures::convert_signature<SIGNATURE>::type, self_type> > aux_type; \
    BOOST_PP_CAT(NAME, _definition)(jobject obj)                        \
      : aux_type(obj) {}                                                \
    typedef self_type this_type;                                    \
    typedef boost::mpl::identity< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type sig_type; \
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

#define JVB_ADAPT_CLASS_METHOD_DEF_STATIC(NAME, SIGNATURE, MODIFIERS)   \
  struct BOOST_PP_CAT(NAME, _definition)                                \
    : ::jvb::detail::function_set                                       \
  <                                                                     \
    boost::function_types::parameter_types< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type     \
   , boost::function_types::result_type< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type       \
   , ::jvb::function_static_definition_object                                  \
   <BOOST_PP_CAT(NAME, _definition),  ::jvb::signatures::convert_signature<SIGNATURE>::type, self_type> >            \
  {                                                                     \
    typedef ::jvb::detail::function_set                                 \
      <                                                                 \
       boost::function_types::parameter_types< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type \
       , boost::function_types::result_type< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type   \
       , ::jvb::function_static_definition_object                              \
       <BOOST_PP_CAT(NAME, _definition),  ::jvb::signatures::convert_signature<SIGNATURE>::type, self_type> > aux_type; \
    BOOST_PP_CAT(NAME, _definition)(jclass cls)                        \
      : aux_type(cls) {}                                               \
    typedef self_type this_type;                                    \
    typedef boost::mpl::identity< ::jvb::signatures::convert_signature<SIGNATURE>::type>::type sig_type;             \
    static const std::size_t name_size = sizeof(BOOST_PP_STRINGIZE(NAME))-1; \
    static const char* name()                                           \
    {                                                                   \
      return BOOST_PP_STRINGIZE(NAME);                                  \
    }                                                                   \
  };                                                                    \
  static BOOST_PP_CAT(NAME, _definition) NAME(::jvb::environment e)    \
  {                                                                     \
    return BOOST_PP_CAT(NAME, _definition)(::jvb::Class(e, name()).raw()); \
  }


#endif

