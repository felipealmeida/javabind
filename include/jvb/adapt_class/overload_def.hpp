// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_CLASS_OVERLOAD_DEF_HPP
#define JVB_ADAPT_CLASS_OVERLOAD_DEF_HPP

#include <jvb/overload_definition.hpp>

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS_DEF(NAME, SIGNATURES)   \
  struct BOOST_PP_CAT(NAME, _definition)                                \
    : ::jvb::detail::overload_set                                       \
  <boost::mpl::vector<BOOST_PP_SEQ_ENUM(SIGNATURES)>                    \
    , void                                                              \
    , ::jvb::overload_definition_object                                 \
   <BOOST_PP_CAT(NAME, _definition), self_type                          \
    , BOOST_PP_SEQ_ENUM(SIGNATURES)> >                                  \
  {                                                                     \
    typedef ::jvb::detail::overload_set                                       \
  <boost::mpl::vector<BOOST_PP_SEQ_ENUM(SIGNATURES)>                    \
    , void                                                              \
    , ::jvb::overload_definition_object                                 \
   <BOOST_PP_CAT(NAME, _definition), self_type                          \
    , BOOST_PP_SEQ_ENUM(SIGNATURES)> > aux_type;                        \
    BOOST_PP_CAT(NAME, _definition)(jobject obj)                        \
      : aux_type(obj) {}                                                \
    typedef self_type this_type;                                    \
    static const std::size_t name_size = sizeof(BOOST_PP_STRINGIZE(NAME))-1; \
    static const char* name()                                           \
    {                                                                   \
      return BOOST_PP_STRINGIZE(NAME);                                  \
    }                                                                   \
  };                                                                    \
  BOOST_PP_CAT(NAME, _definition) NAME() const                          \
  {                                                                     \
    return BOOST_PP_CAT(NAME, _definition)(raw());                      \
  }


#endif
