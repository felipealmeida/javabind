// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_CLASS_HPP
#define JVB_ADAPT_CLASS_HPP

#include <jvb/jvb.hpp>
#include <jvb/function_definition.hpp>
#include <jvb/field.hpp>
#include <jvb/primitives.hpp>
#include <jvb/string.hpp>
#include <jvb/object.hpp>
#include <jvb/detail/preprocessor/seq_filler.hpp>
#include <jvb/detail/max_args.hpp>
#include <jvb/detail/overload_matches.hpp>
#include <jvb/adapt_class/attribute_def.hpp>
#include <jvb/adapt_class/overload_def.hpp>
#include <jvb/adapt_class/method_def.hpp>

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
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/copy_if.hpp>

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS_SEQ_M(R, DATA, OVERLOAD) \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS_DEF OVERLOAD

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS_FOR_EACH(OVERLOADS)   \
  BOOST_PP_SEQ_FOR_EACH(JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS_SEQ_M \
                        , ~, OVERLOADS)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHOD_M(R, DATA, ELEM)   \
  JVB_ADAPT_CLASS_METHOD_DEF ELEM

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_SEQ_M(R, DATA, I, ELEM)    \
  BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, ELEM), _definition)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH(METHODS)        \
  BOOST_PP_SEQ_FOR_EACH(JVB_ADAPT_CLASS_MEMBER_DEFINE_METHOD_M, ~, METHODS) \
  boost::mpl::vector                                                    \
  <BOOST_PP_SEQ_FOR_EACH_I                                              \
   (JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_SEQ_M, ~, METHODS)> all_methods;

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTE_M(R, DATA, ATTRIBUTE)   \
  JVB_ADAPT_CLASS_ATTRIBUTE_DEF ATTRIBUTE

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES_FOR_EACH(ATTRIBUTES)   \
  BOOST_PP_SEQ_FOR_EACH(JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTE_M, ~, ATTRIBUTES)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_CONSTRUCTORS_FOR_EACH(CONSTRUCTORS) \
  typedef boost::mpl::vector                                            \
  <BOOST_PP_SEQ_ENUM(CONSTRUCTORS)>                                     \
  all_constructors;

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS(OVERLOADS)              \
  JVB_PP_CALL_FILLED(JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS_FOR_EACH, OVERLOADS)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS(METHODS)                 \
  JVB_PP_CALL_FILLED(JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS_FOR_EACH, METHODS)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES(ATTRIBUTES)            \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES_FOR_EACH(JVB_PP_CALL_FILL(3, ATTRIBUTES))

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_CONSTRUCTORS(SIGNATURES)  \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_CONSTRUCTORS_FOR_EACH(SIGNATURES)

#define JVB_ADAPT_CLASS_MEMBER_EAT_EXTENDS(CLASS)

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_overloads \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_OVERLOADS BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_methods \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_METHODS BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_attributes \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_ATTRIBUTES BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_constructors \
  JVB_ADAPT_CLASS_MEMBER_DEFINE_CONSTRUCTORS BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_extends \
  JVB_ADAPT_CLASS_MEMBER_EAT_EXTENDS BOOST_PP_LPAREN()

#define JVB_ADAPT_CLASS_MEMBER_DEFINE_AUX_NAME_implements \
  JVB_ADAPT_CLASS_MEMBER_EAT_EXTENDS BOOST_PP_LPAREN()

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

#define JVB_ADAPT_CLASS_CONSTRUCTORS_GENERIC(Z, N, DATA)                \
  template <typename E                                                  \
  BOOST_PP_ENUM_TRAILING_PARAMS_Z(Z, N, typename A)                     \
    >                                                                   \
  DATA ( E e BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(Z, N, A, a)) \
  : base_type( ::jvb::detail::new_object_functor<base_type>()         \
              (e, ::jvb::class_(e, name())                              \
               , jvb::constructors<void(BOOST_PP_ENUM_PARAMS_Z(Z, N, A))> \
               (e, ::jvb::class_(e, name())).raw()))                    \
  {                                                                     \
    typedef ::boost::mpl::copy_if<all_constructors                      \
                                  , typename ::boost::mpl::lambda       \
                                  < ::jvb::detail::is_parameter_size_equal_to \
                                    < ::boost::mpl::_1, ::boost::mpl::size_t<N> > >::type>::type overload_set; \
    BOOST_MPL_ASSERT(( ::boost::mpl::and_ \
                       < ::boost::is_same<typename ::boost::remove_cv<E>::type, ::jvb::environment> \
                       , ::boost::mpl::not_< ::boost::mpl::equal_to< ::boost::mpl::size<overload_set> \
                       , ::boost::mpl::int_<0> > > >));                 \
  }

#define JVB_ADAPT_CLASS(C, MODIFIERS, MEMBERS)                         \
  struct JVB_ADAPT_CLASS_NAME(C) : jvb::object                         \
  {                                                                     \
    typedef JVB_ADAPT_CLASS_NAME(C) self_type;                         \
    typedef jvb::object base_type;                                      \
    JVB_ADAPT_CLASS_NAME(C) ( ::JNIEnv* env, ::jvb::detail::hidden_object o) \
      : base_type(env, o) {}                                            \
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
    BOOST_PP_EXPAND                                                     \
      (BOOST_PP_IIF                                                     \
      (BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(MEMBERS), 4)                  \
       , JVB_ADAPT_CLASS_EXPAND_MEMBER, JVB_ADAPT_CLASS_NO_EXPAND_MEMBER) \
       (4, MEMBERS) BOOST_PP_RPAREN())                                  \
    static const std::size_t name_size =                                \
      sizeof(JVB_ADAPT_CLASS_PACKAGE_AND_NAME_STRING(C)) - 1;          \
    static const char* name()                                           \
    {                                                                   \
      return JVB_ADAPT_CLASS_PACKAGE_AND_NAME_STRING(C);               \
    }                                                                   \
    BOOST_PP_REPEAT(JVB_MAX_ARGS, JVB_ADAPT_CLASS_CONSTRUCTORS_GENERIC  \
                    , JVB_ADAPT_CLASS_NAME(C))                          \
  };                                                                \
  bool operator==(JVB_ADAPT_CLASS_NAME(C) const& lhs, JVB_ADAPT_CLASS_NAME(C) const& rhs);

#endif
