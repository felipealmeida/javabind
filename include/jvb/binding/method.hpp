// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_METHOD_HPP
#define JVB_BINDING_METHOD_HPP

#include <jvb/binding/placeholder/method_value.hpp>

#include <boost/proto/proto.hpp>

namespace jvb { namespace binding {

template <typename ModifierExpr, typename F>
expr<typename boost::proto::terminal
<placeholder::method_value<typename detail::create_signature<F>::type, F> >::type>
method(ModifierExpr modifier_expr, const char* name, F f)
{
  typedef typename detail::create_signature<F>::type signature_type;
  typename boost::proto::terminal<placeholder::method_value<signature_type, F> >::type r =
    { placeholder::method_value<signature_type, F>(f, name) };
  return r;
}

} }

#endif
