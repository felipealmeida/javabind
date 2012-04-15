// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_CREATE_PRIMITIVE_TYPE_DESCRIPTOR_HPP
#define JAVABIND_DETAIL_CREATE_PRIMITIVE_TYPE_DESCRIPTOR_HPP

#include <javabind/field_descriptor_traits.hpp>
#include <javabind/detail/tag.hpp>

#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>

#include <boost/fusion/iterator/next.hpp>

#include <cstring>

namespace javabind {

struct object;

namespace detail {

template <typename First, typename Last>
struct create_primitive_type_descriptor
{
  template <typename DescriptorFirst, typename DescriptorLast>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag<javabind::object>)
  {
    return create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::length(boost::fusion::next(first), last)
      + std::strlen(*first) + 2;
  }

  template <typename DescriptorFirst, typename DescriptorLast, typename T>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag<T>)
  {
    return create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::length(boost::fusion::next(first), last) + 1;
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static std::size_t length(DescriptorFirst first, DescriptorLast last)
  {
    return length_aux(first, last, tag<typename boost::mpl::deref<First>::type>());
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag<javabind::object>)
  {
    std::size_t s = std::strlen(*first);
    v[0] = 'L';
    std::memcpy(v+1, *first, s);
    v[s+1] = ';';
    create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::run(v + s + 2, boost::fusion::next(first), last);
  }

  template <typename DescriptorFirst, typename DescriptorLast, typename T>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag<T>)
  {
    v[0] = field_descriptor_traits<typename boost::mpl::deref<First>::type>::value[0];
    create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::run(v + 1, first, last);
  }

  template <typename T>
  static void check_primitive(tag<T>)
  {
    BOOST_MPL_ASSERT((boost::mpl::not_<boost::is_same<T, object> >));
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static void run(char* v, DescriptorFirst first, DescriptorLast last)
  {
    run_aux(v, first, last, tag<typename boost::mpl::deref<First>::type>());
  }

  static void run(char* v)
  {
    check_primitive(tag<typename boost::mpl::deref<First>::type>());
    v[0] = field_descriptor_traits<typename boost::mpl::deref<First>::type>::value[0];
    create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::run(v + 1);
  }
};

template <typename Last>
struct create_primitive_type_descriptor<Last, Last>
{
  template <typename DescriptorLast>
  static void run(char*, DescriptorLast, DescriptorLast) {}

  static void run(char*) {}

  template <typename DescriptorLast>
  static std::size_t length(DescriptorLast, DescriptorLast) { return 0; }
};

} }

#endif

