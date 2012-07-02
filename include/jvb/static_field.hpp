// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_STATIC_FIELD_HPP
#define JVB_STATIC_FIELD_HPP

#include <jvb/class.hpp>

namespace jvb {

template <typename T>
struct static_field : T
{
  typedef T base_type;

  static_field(environment e, Class const& cls, const char* name)
    : base_type(e, find_static_field(e, cls, name))
  {
  }

private:
  static jobject find_static_field(environment e, Class const& cls, const char* name)
  {
    typedef typename T::class_type class_type;
    class_type class_(e);
    std::string class_name = "L" + class_.name(e) + ";";
    std::cout << "class_name " << class_name << std::endl;
    std::cout << "field name " << name << std::endl;
    std::cout << "from class: " << cls.name(e) << std::endl;
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
