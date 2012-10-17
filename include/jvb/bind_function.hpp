// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BIND_FUNCTION_HPP
#define JVB_BIND_FUNCTION_HPP

#include <jvb/class.hpp>
#include <jvb/environment.hpp>
#include <jvb/object.hpp>
#include <jvb/detail/native_functions.hpp>
#include <jvb/detail/function_safe_cast.hpp>
#include <jvb/detail/descriptors.hpp>
#include <jvb/detail/create_signature.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_type.hpp>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/pop_front.hpp>

namespace jvb {

template <typename Signature, typename F>
void bind_function(environment e, Class cls, const char* name)
{
  typedef typename boost::function_types::result_type<Signature>::type return_type;
  typedef typename boost::function_types::parameter_types<Signature>
    ::type parameter_types;
  typedef typename boost::mpl::size<parameter_types>::type size_type;
  BOOST_MPL_ASSERT_RELATION(size_type::value, >=, 2);
  typedef typename boost::mpl::at_c<parameter_types, 0>::type parameter_first_type;
  typedef typename boost::mpl::at_c<parameter_types, 1>::type parameter_second_type;
  BOOST_MPL_ASSERT((boost::is_same<parameter_first_type, environment>));
  BOOST_MPL_ASSERT((boost::is_same<parameter_second_type, Object>));
  typedef typename boost::mpl::pop_front
    <typename boost::mpl::pop_front<parameter_types>::type>::type
    new_parameter_types;
  BOOST_MPL_ASSERT((boost::mpl::equal_to
                    <typename boost::mpl::size<new_parameter_types>::type
                    , boost::mpl::size_t<size_type::type::value-2> >));
  // typedef typename boost::function_types::function_type
  //   <boost::mpl::joint_view
  //    <boost::mpl::single_view<return_type>, new_parameter_types>
  //    >::type signature_type;
  std::string type;
  detail::descriptors::descriptor_function<return_type, new_parameter_types>
    (e, std::back_inserter<std::string>(type));
  assert(e.raw()->GetMethodID(cls.raw(), name, type.c_str()));

  JNINativeMethod methods[1];
  methods[0].name = const_cast<char*>(name);
  methods[0].signature = const_cast<char*>(type.c_str());
  methods[0].fnPtr = detail::function_safe_cast
    (&detail::native_function<F, boost::mpl::vector0<> >);

  if(e.raw()->RegisterNatives(cls.raw(), methods, 1) < 0)
  {
    throw std::runtime_error("Error registering native function");
  }
  else
    std::cout << "Registered with success" << std::endl;
}

}

#endif
