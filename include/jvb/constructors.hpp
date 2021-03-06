// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CONSTRUCTORS_HPP
#define JVB_CONSTRUCTORS_HPP

#include <jvb/class.hpp>
#include <jvb/environment.hpp>
#include <jvb/detail/descriptors.hpp>

#include <boost/function_types/parameter_types.hpp>

#include <jni.h>

namespace jvb {

template <typename F>
struct constructors
{
  constructors() : method_id(0)
  {}
  constructors(environment e, Class const& cls)
  : cls(cls), method_id(find_id(e, cls))
  {}

  Class class_() const { return cls; }
  jmethodID raw () const { return method_id; }
private:
  static jmethodID find_id(environment e, Class cls)
  {
    std::string descriptor;
    jvb::detail::descriptors::descriptor_function
      <void, typename boost::function_types::parameter_types<F>::type>
      (e, std::back_inserter(descriptor));
    jmethodID id = e.raw()->GetMethodID(cls.raw(), "<init>", descriptor.c_str());
    assert(id != 0);
    return id;
  }

  Class cls;
  jmethodID method_id;
};

}

#endif
