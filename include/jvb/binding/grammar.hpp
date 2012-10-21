// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_GRAMMAR_HPP
#define JVB_BINDING_GRAMMAR_HPP

#include <jvb/binding/placeholder/method_value.hpp>
#include <boost/proto/proto.hpp>

namespace jvb { namespace binding {

namespace proto = boost::proto;

struct grammar
  : proto::or_
    <
      proto::terminal<binding::placeholder::method_value<proto::_, proto::_> >
      , proto::comma<grammar, grammar>
    >
{};


} }

#endif
