// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_BIND_FUNCTIONS_TRANSFORM_HPP
#define JVB_BINDING_BIND_FUNCTIONS_TRANSFORM_HPP

#include <jvb/binding/placeholder/method.hpp>
#include <jvb/class_file/class_.hpp>
#include <jvb/detail/descriptors.hpp>

#include <boost/proto/proto.hpp>
#include <boost/proto/traits.hpp>

namespace jvb { namespace binding {

namespace proto = boost::proto;

struct method_function
{
  typedef void result_type;
  result_type operator()(jvb::environment e, jvb::Object obj) const
  {
    std::cout << "method_function" << std::endl;
  }
};

struct bind_method_call : proto::callable
{
  typedef void result_type;
  template <typename Sig, typename F>
  void operator()(binding::placeholder::method_value<Sig, F>const& method
                  , Class const& cls, environment e) const
  {
    std::cout << "bind_method_call" << std::endl;
    jvb::bind_function<void(jvb::environment, jvb::Object)
                       , binding::method_function>
      (e, cls, method.name);
  }
};

struct bind_functions_transform
  : proto::when
  <
    proto::terminal<binding::placeholder::method_value<proto::_,proto::_> >
  , bind_method_call(proto::_value, proto::_state, proto::_data)
  >
{};

} }

#endif
