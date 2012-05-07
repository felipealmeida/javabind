// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_WRAP_ARGUMENT_HPP
#define JAVABIND_DETAIL_WRAP_ARGUMENT_HPP

#include <javabind/primitives.hpp>
#include <javabind/type_mapping.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/not.hpp>

namespace javabind { namespace detail { namespace wrap_argument_detail {

template <typename T>
T wrap_argument_aux(typename type_mapping<T>::java_type o
                    , JNIEnv* env, tag<T>
                    , typename boost::enable_if
                    <boost::mpl::and_
                    <typename type_mapping<T>::is_primitive
                     , boost::mpl::not_<typename type_mapping<T>::is_array> >
                     , void*>::type = 0)
{
  return T(o);
}

template <typename T>
T wrap_argument_aux(typename type_mapping<T>::java_type o
                    , JNIEnv* env, tag<T>
                    , typename boost::enable_if
                    <typename boost::mpl::or_
                     <boost::mpl::not_<typename type_mapping<T>::is_primitive>
                      , typename type_mapping<T>::is_array>
                     , void*>::type = 0)
{
  return T(o, env);
}

}

template <typename T, typename U>
T wrap_argument(U obj, JNIEnv* env)
{
  return wrap_argument_detail::wrap_argument_aux(obj, env, tag<T>());
}



} }

#endif
