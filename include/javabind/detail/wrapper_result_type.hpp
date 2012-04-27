// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_WRAPPER_RESULT_TYPE_HPP
#define JAVABIND_DETAIL_WRAPPER_RESULT_TYPE_HPP

#include <boost/mpl/transform.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>

namespace javabind { namespace detail {

template <typename R, typename S, bool is_static>
struct wrapper_result_type
{
  struct transformation_op
  {
    template <typename T>
    struct apply
    {
      typedef typename type_mapping<T>::java_type type;
    };
  };

  typedef typename boost::mpl::apply_wrap1<transformation_op, R>::type
    call_result_type;

  typedef typename boost::function_types::function_pointer
  <typename boost::mpl::push_front // result
   <typename boost::mpl::push_front // JNIEnv*
    <typename boost::mpl::push_front // jobject/jclass self
     <typename boost::mpl::transform<S, transformation_op>::type
      , typename boost::mpl::if_c<is_static, jclass, jobject>::type>::type
     , JNIEnv*>::type
    , call_result_type
    >::type
   >::type type;
};

} }

#endif
