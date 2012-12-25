// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_WRAP_ARGUMENT_HPP
#define JVB_DETAIL_WRAP_ARGUMENT_HPP

#include <jvb/primitives.hpp>
#include <jvb/type_mapping.hpp>
#include <jvb/detail/hidden_object.hpp>
#include <jvb/detail/tag.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/not.hpp>

namespace jvb { namespace detail { namespace wrap_argument_detail {

template <typename T>
T wrap_argument_aux(typename type_mapping<T>::java_type o
                    , JNIEnv* env, tag<T>
                    , typename boost::enable_if
                    <mpl::and_
                    <typename type_mapping<T>::is_primitive
                     , mpl::not_<typename type_mapping<T>::is_array> > >::type* = 0)
{
  return T(o);
}

template <typename T>
T wrap_argument_aux(typename type_mapping<T>::java_type o
                    , JNIEnv* env, tag<T>
                    , typename boost::enable_if
                    <typename mpl::and_
                     <mpl::not_<typename type_mapping<T>::is_primitive>
                      , mpl::not_<typename type_mapping<T>::is_array> > >::type* = 0)
{
  return T(env, hidden_object(o));
}

template <typename T>
T wrap_argument_aux(typename type_mapping<T>::java_type o
                    , JNIEnv* env, tag<T>
                    , typename boost::enable_if<typename type_mapping<T>::is_array>::type* = 0)
{
  return T(environment(env), o);
}

}

template <typename T, typename U>
T wrap_argument(U obj, JNIEnv* env)
{
  return wrap_argument_detail::wrap_argument_aux(obj, env, tag<T>());
}



} }

#endif
