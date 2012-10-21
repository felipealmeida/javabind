// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_DOMAIN_HPP
#define JVB_BINDING_DOMAIN_HPP

#include <boost/proto/proto.hpp>

namespace jvb { namespace binding {

template <typename Expr>
struct expr;

struct grammar;

struct domain
  : boost::proto::domain<boost::proto::generator<expr>, grammar>
{};

} }

#endif
