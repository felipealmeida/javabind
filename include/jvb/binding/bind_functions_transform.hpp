// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_BIND_FUNCTIONS_TRANSFORM_HPP
#define JVB_BINDING_BIND_FUNCTIONS_TRANSFORM_HPP

#include <jvb/binding/placeholder/method_value.hpp>
#include <jvb/binding/method_function.hpp>
#include <jvb/binding/method_traits.hpp>
#include <jvb/binding/virtual_table.hpp>
#include <jvb/binding/grammar.hpp>
#include <jvb/class_file/class_.hpp>
#include <jvb/detail/descriptors.hpp>

#include <boost/proto/proto.hpp>
#include <boost/proto/traits.hpp>
#include <boost/mpl/plus.hpp>

namespace jvb { namespace binding {

namespace proto = boost::proto;
namespace mpl = boost::mpl;

template <typename PeerClass>
struct bind_method_call : proto::callable
{
  template <typename T>
  struct result
  {
    typedef typename boost::function_types::parameter_types<T>::type parameter_types;
    typedef typename boost::mpl::next
    <typename boost::remove_reference
     <typename boost::mpl::at_c<parameter_types, 2u>::type>::type>::type type;
  };

  template <typename FD, typename FO, typename FS, std::size_t I, std::size_t N>
  boost::mpl::size_t<I+1>
  operator()(binding::placeholder::method_value<FD, FO, FS>const& method
             , boost::fusion::vector<Class&, environment, binding::virtual_table<N>&>& data
             , boost::mpl::size_t<I> v) const
  {
    Class& cls = boost::fusion::at_c<0>(data);
    environment e = boost::fusion::at_c<1>(data);
    binding::virtual_table<N>& virtual_table = boost::fusion::at_c<2>(data);

    typedef binding::method_traits<FS> method_traits;
    typedef typename method_traits::result_type result_type;

    std::cout << "bind_method_call" << std::endl;
    jvb::bind_function<result_type(jvb::environment, jvb::Object)
                       , binding::method_function<I, N, result_type, PeerClass> >
      (e, cls, FD::name());

    typedef typename method_traits::template function_caller<FO> function_caller_type;

    virtual_table.methods[I].function_object =
      boost::shared_ptr<void>
      (new boost::function<result_type(PeerClass&, jvb::environment)>
       (function_caller_type(method.f)));

    std::cout << "typeid(FS) " << typeid(FS).name() << std::endl;

    return boost::mpl::size_t<I+1>();
  }
};

template <typename PeerClass>
struct bind_functions_transform
  : proto::or_
    <proto::when
     <
       proto::terminal<binding::placeholder::method_value<proto::_,proto::_, proto::_> >
     , proto::call<bind_method_call<PeerClass>(proto::_value, proto::_data, proto::_state)>
    >
    , proto::when
    <
      proto::comma<bind_functions_transform<PeerClass>, bind_functions_transform<PeerClass> >
    , proto::call<bind_functions_transform<PeerClass>
                  (proto::_left
                   , proto::call<bind_functions_transform<PeerClass>
                   (proto::_right, proto::_state, proto::_data)>
                   , proto::_data)>
    >
   >
{};

struct count_virtual_table_transform
  : proto::or_
    <proto::when
     <
       proto::terminal<binding::placeholder::method_value<proto::_,proto::_, proto::_> >
       , boost::mpl::size_t<1>()
     >
     , proto::when
     <
       proto::comma<count_virtual_table_transform, count_virtual_table_transform>
       , mpl::plus<count_virtual_table_transform(proto::_left)
                   , count_virtual_table_transform(proto::_right)>()
     >
   >
{};

} }

#endif
