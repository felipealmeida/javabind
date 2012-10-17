// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_STATIC_FIELD_HPP
#define JVB_STATIC_FIELD_HPP

#include <jvb/class.hpp>
#include <jvb/detail/descriptors.hpp>

#include <iterator>

namespace jvb {

template <typename T>
struct static_field : T
{
  typedef T base_type;

  template <typename C>
  static_field(environment e, C const& cls, const char* name)
    : base_type(e, find_static_field(e, cls, name))
  {
  }

private:
  static jobject find_static_field(environment e, Class const& cls, const char* name)
  {
    typedef typename T::class_type class_type;
    std::cout << "T: " << typeid(T).name() << " " << typeid(typename T::class_type).name() << std::endl;
    std::string class_name;
    jvb::detail::descriptors::descriptor<class_type>
      (e, std::back_inserter(class_name));
    std::cout << "class_name: " << class_name << std::endl;
    jfieldID fid = e.raw()->GetStaticFieldID(cls.raw(), name, class_name.c_str());
    assert(fid != 0);
    jobject obj = e.raw()->GetStaticObjectField(cls.raw(), fid);
    assert(obj != 0);
    std::cout << "obj: " << obj << std::endl;
    return obj;
  }
};

}

#endif
