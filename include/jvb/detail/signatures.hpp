// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ADAPT_SIGNATURES_HPP
#define JVB_ADAPT_SIGNATURES_HPP

#include <jvb/object.hpp>

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/transform.hpp>
#include <boost/mpl/contains.hpp>

#include <boost/type_traits.hpp>

namespace jvb {

namespace detail {

template <typename T, typename Enable = void>
struct signature_transform;

template <> struct signature_transform<char> { typedef char_ type; };
template <> struct signature_transform<short> { typedef short_ type; };
template <> struct signature_transform<int> { typedef int_ type; };
template <> struct signature_transform<long> { typedef long_ type; };
template <> struct signature_transform<float> { typedef float_ type; };
template <> struct signature_transform<double> { typedef double_ type; };

template <typename T>
struct signature_transform
 <T
  , typename boost::disable_if
    <boost::is_array<typename boost::remove_reference<T>::type> >::type
 >
{
  typedef typename boost::remove_reference<T>::type type;
};

template <typename T>
struct signature_transform
 <T
  , typename boost::enable_if
    <boost::is_array<typename boost::remove_reference<T>::type> >::type
 >
{
  BOOST_MPL_ASSERT((boost::is_array<typename boost::remove_reference<T>::type>));
  typedef jvb::array
    <typename signature_transform
     <typename boost::remove_extent
      <typename boost::remove_reference<T>::type>::type>::type> type;
};

}
 
namespace signatures {

namespace mpl = boost::mpl;

typedef bool boolean;
typedef jvb::byte byte;

template <typename Sig>
struct convert_signature
{
  typedef typename boost::function_types::result_type<Sig>::type result_type;
  typedef typename boost::function_types::parameter_types<Sig>::type parameter_types;

  typedef typename mpl::transform<parameter_types
                                  , detail::signature_transform<mpl::_> >::type
    new_parameter_types;
  typedef typename detail::signature_transform<result_type>::type new_result_type;

  typedef mpl::not_<boost::is_same
  < typename mpl::find_if
    <parameter_types, boost::is_array<mpl::_> >::type
    , typename mpl::end<parameter_types>::type
  > >
    contains_array;

  typedef mpl::not_<boost::is_same
  < typename mpl::find_if
    <new_parameter_types, boost::is_array<mpl::_> >::type
    , typename mpl::end<new_parameter_types>::type
  > >
    new_contains_array;
  BOOST_MPL_ASSERT((mpl::not_<new_contains_array>));

  typedef typename boost::function_types::function_type
  <typename mpl::push_front<new_parameter_types, new_result_type>::type>::type type;
};

} }

#endif
