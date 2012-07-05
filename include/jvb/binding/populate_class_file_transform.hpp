// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_POPULATE_CLASS_FILE_CONTEXT_HPP
#define JVB_BINDING_POPULATE_CLASS_FILE_CONTEXT_HPP

#include <jvb/binding/placeholder/method.hpp>
#include <jvb/class_file/class_.hpp>
#include <jvb/detail/descriptors.hpp>

#include <boost/proto/proto.hpp>
#include <boost/proto/traits.hpp>

namespace jvb { namespace binding {

namespace proto = boost::proto;

struct add_method_call : proto::callable
{
  typedef void result_type;
  template <typename Sig, typename F>
  void operator()(binding::placeholder::method_value<Sig, F>const& method
                  , class_files::class_& cf) const
  {
    class_files::not_implemented_method m = {method.name};
    typedef typename boost::function_types::result_type<Sig>::type return_type;
    typedef typename boost::function_types::parameter_types<Sig>::type parameter_types;
    detail::descriptors::descriptor_function<return_type, parameter_types>
      (std::back_inserter(m.descriptor));
    cf.not_implemented_methods.push_back(m);
  }
};

struct populate_class_file_transform
  : proto::when
  <
    proto::terminal<binding::placeholder::method_value<proto::_,proto::_> >
  , add_method_call(proto::_value, proto::_state)
  >
{};

} }

#endif
