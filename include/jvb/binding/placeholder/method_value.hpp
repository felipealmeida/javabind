// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_PLACEHOLDER_METHOD_VALUE_HPP
#define JVB_BINDING_PLACEHOLDER_METHOD_VALUE_HPP

#include <jvb/binding/expr.hpp>

#include <boost/proto/proto.hpp>

namespace jvb { namespace binding { namespace placeholder {

template <typename Signature, typename F, typename FunctionType = F>
struct method_value
{
  method_value(F f, const char* name)
    : f(f), name(name) {}

  F f;
  const char* name;
};

} } }

#endif
