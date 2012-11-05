// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_CLASS_ATTRIBUTE_DEF_HPP
#define JVB_ADAPT_CLASS_ATTRIBUTE_DEF_HPP

#include <jvb/detail/preprocessor/modifiers_sequence.hpp>

#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/seq/filter.hpp>

#define JVB_ADAPT_CLASS_HAS_STATIC_CHOOSE_static 1
#define JVB_ADAPT_CLASS_HAS_STATIC_CHOOSE_final

#define JVB_ADAPT_CLASS_HAS_STATIC_PRED(S, DATA, M)   \
  BOOST_PP_CAT(JVB_ADAPT_CLASS_HAS_STATIC_CHOOSE_, M)

#define JVB_ADAPT_CLASS_HAS_STATIC_ITERATE_0(M) \
  BOOST_PP_CAT(JVB_ADAPT_CLASS_HAS_STATIC_CHOOSE_, M) JVB_ADAPT_CLASS_HAS_STATIC_ITERATE_1
#define JVB_ADAPT_CLASS_HAS_STATIC_ITERATE_1(M) \
  BOOST_PP_CAT(JVB_ADAPT_CLASS_HAS_STATIC_CHOOSE_, M) JVB_ADAPT_CLASS_HAS_STATIC_ITERATE_0
#define JVB_ADAPT_CLASS_HAS_STATIC_ITERATE_0_END
#define JVB_ADAPT_CLASS_HAS_STATIC_ITERATE_1_END

#define JVB_ADAPT_CLASS_HAS_STATIC(MODIFIERS)   \
  BOOST_PP_CAT(JVB_ADAPT_CLASS_HAS_STATIC_ITERATE_0 MODIFIERS, _END)


#define JVB_ADAPT_CLASS_ATTRIBUTE_DEF_CHECK_STATIC(NAME, TYPE, MODIFIERS) \
  BOOST_PP_IF(BOOST_PP_IS_EMPTY                                         \
              (JVB_ADAPT_CLASS_HAS_STATIC(JVB_ADAPT_CLASS_MODIFIERS_SEQ(MODIFIERS))) \
                , JVB_ADAPT_CLASS_ATTRIBUTE_DEF_NO_STATIC               \
              , JVB_ADAPT_CLASS_ATTRIBUTE_DEF_STATIC)(NAME, TYPE, MODIFIERS)


#define JVB_ADAPT_CLASS_ATTRIBUTE_DEF_CONSUME_IF_NIL_nil

#define JVB_ADAPT_CLASS_ATTRIBUTE_DEF(NAME, TYPE, MODIFIERS)            \
  BOOST_PP_IF(BOOST_PP_IS_EMPTY                                         \
              (BOOST_PP_CAT(JVB_ADAPT_CLASS_ATTRIBUTE_DEF_CONSUME_IF_NIL_, MODIFIERS)) \
              , JVB_ADAPT_CLASS_ATTRIBUTE_DEF_NO_STATIC                 \
              , JVB_ADAPT_CLASS_ATTRIBUTE_DEF_CHECK_STATIC)(NAME, TYPE, MODIFIERS)

#define JVB_ADAPT_CLASS_ATTRIBUTE_DEF_STATIC(NAME, TYPE, MODIFIERS)     \
  struct BOOST_PP_CAT(NAME, _definition)                                \
  {                                                                     \
    BOOST_PP_CAT(NAME, _definition)( ::jvb::environment e)              \
      : e(e), cls(e, self_type::name()) {}                              \
    TYPE operator()() const                                           \
    {                                                                 \
      return ::jvb::read_static_field<self_type, TYPE>(e, cls, name()); \
    }                                                                   \
    bool operator==(TYPE other) const                                   \
    {                                                                   \
      TYPE self = (*this)();                                            \
      return self == other;                                             \
    }                                                                   \
    BOOST_PP_CAT(NAME, _definition) const& operator=(TYPE x) const      \
    {                                                                 \
      ::jvb::write_static_field<self_type>(e, cls, name(), x);          \
      return *this;                                                     \
    }                                                                   \
    static const std::size_t name_size = sizeof(BOOST_PP_STRINGIZE(NAME))-1; \
    static const char* name()                                           \
    {                                                                   \
      return BOOST_PP_STRINGIZE(NAME);                                  \
    }                                                                   \
    ::jvb::environment e;                                               \
    ::jvb::class_ cls;                                                  \
  };                                                                    \
  static BOOST_PP_CAT(NAME, _definition) NAME( ::jvb::environment e)    \
  {                                                                     \
    return BOOST_PP_CAT(NAME, _definition) (e);                         \
  }
  
  

#define JVB_ADAPT_CLASS_ATTRIBUTE_DEF_NO_STATIC(NAME, TYPE, MODIFIERS)  \
  struct BOOST_PP_CAT(NAME, _definition)                                \
  {                                                                     \
    BOOST_PP_CAT(NAME, _definition)( ::jvb::environment e, jobject obj) \
      : e(e), obj(obj) {}                                               \
                                                                        \
    TYPE operator()() const                                             \
    {                                                                   \
      return ::jvb::read_field<self_type, TYPE>(e, obj, name());        \
    }                                                                   \
    bool operator==(TYPE other) const                                   \
    {                                                                   \
      TYPE self = (*this)();                                            \
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

#endif

