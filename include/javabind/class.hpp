// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_CLASS_HPP
#define JAVABIND_CLASS_HPP

#include <javabind/method.hpp>
#include <javabind/descriptors.hpp>
#include <javabind/field_descriptor_traits.hpp>
#include <javabind/detail/get_static_field.hpp>
#include <javabind/detail/create_primitive_type_descriptor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

#include <jni.h>

#include <stdexcept>
#include <iostream>
#include <vector>
#include <iterator>

namespace javabind {

template <typename T>
struct static_field;
template <typename T>
struct field;
template <typename T>
struct constructor;

struct class_
{
  class_() : cls(0), env(0) {}
  class_( ::jclass cls, JNIEnv* env)
    : cls(cls), env(env)
  {
  }

  template <typename F>
  javabind::method<F> method(const char* name) const
  {
    typedef typename boost::function_types::parameter_types<F>::type
      parameter_types;
    char type[boost::mpl::size<parameter_types>::type::value+4];
    type[0] = '(';
    type[sizeof(type)-3] = ')';
    type[sizeof(type)-2] = field_descriptor_traits      
      <typename boost::function_types::result_type<F>::type>::value[0];
    type[sizeof(type)-1] = 0;
    detail::create_primitive_type_descriptor
      <typename boost::mpl::begin<parameter_types>::type
       , typename boost::mpl::end<parameter_types>::type>::run(type+1);
    std::cout << "NS Using as type: " << type << std::endl;
    jmethodID id = env->GetMethodID(cls, name, type);
    if(id == 0)
      throw std::runtime_error("Couldn't find method");
    return javabind::method<F>
      (id, env);
  }

  template <typename F, typename S>
  javabind::method<F> method(const char* name, S s) const
  {
    typedef typename boost::function_types::parameter_types<F>::type
      parameter_types;
    typedef detail::create_primitive_type_descriptor
      <typename boost::mpl::begin<parameter_types>::type
       , typename boost::mpl::end<parameter_types>::type> create_descriptor;
    std::vector<char> type
      (create_descriptor::length
       (boost::fusion::begin(s)
        , boost::fusion::end(s))+4);
    type[0] = '(';
    type[type.size()-3] = ')';
    type[type.size()-2] = field_descriptor_traits
      <typename boost::function_types::result_type<F>::type>::value[0];
    create_descriptor::run(&type[1], boost::fusion::begin(s), boost::fusion::end(s));
    type[type.size()-1] = 0;
    std::cout << "S Using as type: " << &type[0] << std::endl;
    jmethodID id = env->GetMethodID(cls, name, &type[0]);
    if(id == 0)
      throw std::runtime_error("Couldn't find method");
    return javabind::method<F>
      (id, env);
  }

  template <typename F>
  javabind::constructor<F> constructor() const
  {
    typedef typename boost::function_types::parameter_types<F>::type
      parameter_types;
    char type[boost::mpl::size<parameter_types>::type::value+4];
    type[0] = '(';
    type[sizeof(type)-3] = ')';
    type[sizeof(type)-2] = 'V';
    type[sizeof(type)-1] = 0;
    detail::create_primitive_type_descriptor
      <typename boost::mpl::begin<parameter_types>::type
       , typename boost::mpl::end<parameter_types>::type>::run(type+1);
    std::cout << "C Using as type: " << type << std::endl;
    jmethodID id = env->GetMethodID(cls, "<init>", type);
    if(id == 0)
      throw std::runtime_error("Couldn't find constructor");
    return javabind::constructor<F>(id, env);
  }

  template <typename T>
  javabind::static_field<T> find_static_field(const char* name) const
  {
    jfieldID id = env->GetStaticFieldID(cls, name, field_descriptor_traits<T>::value);
    if(id == 0)
      throw std::runtime_error("Couldn't find field");
    return javabind::static_field<T>(id);
  }

  template <typename T>
  javabind::static_field<T> find_static_field(const char* name, const char* type) const
  {
    jfieldID id = env->GetStaticFieldID(cls, name, type);
    if(id == 0)
      throw std::runtime_error("Couldn't find field");
    return javabind::static_field<T>(id);
  }

  template <typename T>
  javabind::field<T> find_field(const char* name) const
  {
    jfieldID id = env->GetFieldID(cls, name, field_descriptor_traits<T>::value);
    if(id == 0)
      throw std::runtime_error("Couldn't find field");
    return javabind::field<T>(id);
  }

  template <typename T>
  javabind::field<T> find_field(const char* name, const char* type) const
  {
    jfieldID id = env->GetFieldID(cls, name, type);
    if(id == 0)
      throw std::runtime_error("Couldn't find field");
    return javabind::field<T>(id);
  }

  ::jclass raw() const { return cls; }

  ::jclass cls;
  JNIEnv* env;
};

}

#include <javabind/field.hpp>
#include <javabind/constructor.hpp>

#endif
