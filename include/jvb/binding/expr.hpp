// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_EXPR_HPP
#define JVB_BINDING_EXPR_HPP

#include <jvb/binding/domain.hpp>

#include <boost/proto/proto.hpp>

namespace jvb { namespace binding {

template <typename Expr>
struct expr
  : boost::proto::extends<Expr, expr<Expr>, binding::domain>
{
  typedef boost::proto::extends<Expr, expr<Expr>, domain> base_type;

  expr(Expr const& expr = Expr())
    : base_type(expr) {}
};

} }

#endif

