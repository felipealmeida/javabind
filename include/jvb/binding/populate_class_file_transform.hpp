// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_POPULATE_CLASS_FILE_CONTEXT_HPP
#define JVB_BINDING_POPULATE_CLASS_FILE_CONTEXT_HPP

#include <jvb/binding/placeholder/method_value.hpp>
#include <jvb/class_file/class_.hpp>
#include <jvb/detail/descriptors.hpp>

#include <boost/proto/proto.hpp>
#include <boost/proto/traits.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/invoke.hpp>

#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/at.hpp>

namespace jvb { namespace binding {

namespace proto = boost::proto;

struct add_method_call : proto::callable
{
  typedef void result_type;
  template <typename FD, typename FO, typename FS>
  void operator()(binding::placeholder::method_value<FD, FO, FS>const& method
                  , boost::fusion::vector<class_files::class_&, environment> data)
  {
    class_files::class_& cls = boost::fusion::at_c<0>(data);
    environment e = boost::fusion::at_c<1>(data);
    class_files::name_descriptor_pair m;
    boost::fusion::at_c<0>(m) = FD::name();
    typedef typename FD::sig_type sig_type;
    typedef typename boost::function_types::result_type<sig_type>::type return_type;
    typedef typename boost::function_types::parameter_types<sig_type>::type parameter_types;
    detail::descriptors::descriptor_function<return_type, parameter_types>
      (e, std::back_inserter(boost::fusion::at_c<1>(m)));
    cls.not_implemented_methods.push_back(m);
  }
};

struct populate_class_file_transform
  : proto::or_
    <proto::when
     <
       proto::terminal<binding::placeholder::method_value<proto::_,proto::_, proto::_> >
     , add_method_call(proto::_value, proto::_data)
     >
     , proto::when
     <
       proto::comma<populate_class_file_transform, populate_class_file_transform>
     , proto::and_<populate_class_file_transform(proto::_left)
                   , populate_class_file_transform(proto::_right)>()
     >
   >
{};

} }

#endif
