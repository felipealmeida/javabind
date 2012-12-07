// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_OBJECT_HPP
#define JVB_OBJECT_HPP

#include <jvb/class.hpp>
#include <jvb/extends.hpp>
#include <jvb/detail/hidden_object.hpp>

#include <boost/mpl/vector.hpp>

#include <jni.h>
#include <ostream>

namespace jvb {

namespace mpl = boost::mpl;

struct object_class : extends<object_class, class_>
{
  object_class(jvb::environment e, const char* name = "java/lang/Object")
    : base_type(e, name) {}
};

struct object
{
  typedef mpl::vector0<> all_constructors;

  object() : obj(0) {}
  object(environment e, jobject obj)
    : obj(obj)
  {
  }
  object(environment e, detail::hidden_object obj)
    : obj(obj.obj)
  {
  }

  object(jobject obj)
    : obj(obj)
  {
  }

  jvb::class_ class_(environment e) const
  {
    return e.raw()->GetObjectClass(obj);
  }
  jobject raw() const { return obj; }

//   typedef bool(object::*test_type)() const;
//   operator test_type() const
//   {
//     return test()? &object::test : test_type(0);
//   }

//   string to_string() const;
  static object nil() { return object(); }
//   JNIEnv* environment() const { return env; }
  typedef jvb::object_class class_type;
private:
  bool test() const { return obj != 0; }

  ::jobject obj;
};

std::ostream& operator<<(std::ostream& os, object o);

typedef object Object;

namespace jcl { namespace java { namespace lang {

typedef jvb::object Object;

} } }

}

#endif

