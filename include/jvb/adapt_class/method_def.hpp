// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_CLASS_METHOD_DEF_HPP
#define JVB_ADAPT_CLASS_METHOD_DEF_HPP

#define JVB_ADAPT_CLASS_METHOD_DEF(NAME, SIGNATURE)          \
  struct BOOST_PP_CAT(NAME, _definition)                                \
    : ::jvb::detail::function_set                                       \
  <typename boost::mpl::push_front                                      \
  <typename boost::function_types::parameter_types<SIGNATURE>::type     \
   , ::jvb::environment>::type                                              \
   , typename boost::function_types::result_type<SIGNATURE>::type       \
   , ::jvb::function_definition_object                                  \
   <BOOST_PP_CAT(NAME, _definition), SIGNATURE, self_type> >            \
  {                                                                     \
    typedef ::jvb::detail::function_set                                 \
      <typename boost::mpl::push_front                                  \
       <typename boost::function_types::parameter_types<SIGNATURE>::type \
        , ::jvb::environment>::type                                     \
       , typename boost::function_types::result_type<SIGNATURE>::type   \
       , ::jvb::function_definition_object                              \
       <BOOST_PP_CAT(NAME, _definition), SIGNATURE, self_type> > aux_type; \
    BOOST_PP_CAT(NAME, _definition)(jobject obj)                        \
      : aux_type(obj) {}                                                \
    typedef self_type this_type;                                    \
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


#endif

