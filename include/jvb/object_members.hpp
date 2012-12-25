// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_OBJECT_MEMBERS_HPP
#define JVB_OBJECT_MEMBERS_HPP

#include <jvb/object.hpp>
#include <jvb/string.hpp>
#include <jvb/method.hpp>
#include <jvb/error.hpp>
#include <jvb/jcl/java/lang/Throwable.hpp>

namespace jvb {

inline string object::to_string(environment e) const
{
  method<string()> m(e, raw(), "toString");
  return m(e);
}

inline jcl::java::lang::Throwable thrown_error::exception() const
{
  return jcl::java::lang::Throwable(detail::hidden_object(throwable));
}

}

#endif
