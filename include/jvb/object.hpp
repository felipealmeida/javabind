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

struct string;

namespace mpl = boost::mpl;

struct object
{
  typedef mpl::vector0<> all_constructors;
  typedef ::jobject java_type;

  object() : obj(0) {}
  object(detail::hidden_object obj)
    : obj(obj.obj)
  {
  }
  object(jobject obj)
    : obj(obj)
  {
  }

  static const char* name() { return "java/lang/Object"; }
  static const std::size_t name_size = 16;

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

  jvb::string to_string(environment e) const;
  static object nil() { return object(); }
private:
  bool test() const { return obj != 0; }

  ::jobject obj;
};

typedef object Object;

namespace jcl { namespace java { namespace lang {

typedef jvb::object Object;

} } }

}

#endif

