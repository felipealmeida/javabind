// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_STATIC_METHOD_HPP
#define JVB_STATIC_METHOD_HPP

#include <jvb/class.hpp>
#include <jvb/detail/overload_set.hpp>
#include <jvb/detail/select_static_call_functor.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/push_front.hpp>

#include <jni.h>

namespace jvb {

template <typename F>
struct static_method : detail::function_set
  <
    typename boost::function_types::parameter_types<F>::type
  , typename boost::function_types::result_type<F>::type
  , typename detail::select_static_call_functor
   <
     typename boost::function_types::result_type<F>::type
   >::type
  >
{
  typedef typename detail::select_static_call_functor
   <
     typename boost::function_types::result_type<F>::type
   >::type functor_type;
  typedef detail::function_set
  <
    typename boost::function_types::parameter_types<F>::type
   , typename boost::function_types::result_type<F>::type
   , functor_type
  > base_type;
  static_method() : base_type(functor_type(0, 0)) {}
  static_method(environment e, jclass cls, const char* name)
    : base_type(functor_type(cls, find_id(e, cls, name))) {}

  jmethodID raw() const { return base_type::functor().raw(); }

private:
  static jmethodID find_id(environment e, jclass cls, const char* name)
  {
    typedef typename boost::function_types::result_type<F>::type return_type;
    typedef typename boost::function_types::parameter_types<F>::type parameter_types;
    std::string type;
    detail::descriptors::descriptor_function<return_type, parameter_types>
      (e, std::back_inserter<std::string>(type));
    assert(cls != 0);
    jmethodID id = e.raw()->GetStaticMethodID(cls, name, type.c_str());
    assert(id != 0);
    return id;
  }
};

}

#endif
