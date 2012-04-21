// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_DETAIL_CREATE_PRIMITIVE_TYPE_DESCRIPTOR_HPP
#define JAVABIND_DETAIL_CREATE_PRIMITIVE_TYPE_DESCRIPTOR_HPP

#include <javabind/field_descriptor_traits.hpp>
#include <javabind/array.hpp>
#include <javabind/detail/tag.hpp>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>

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

  template <typename DescriptorFirst, typename DescriptorLast>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag< ::jobject>)
  {
    return length_aux(first, last, tag<javabind::object>());
  }

  template <typename DescriptorFirst, typename DescriptorLast, typename T>
  static std::size_t length_array_aux(DescriptorFirst first, DescriptorLast last
                                      , tag<T>)
  {
    typedef boost::mpl::joint_view
      <boost::mpl::single_view<T>
       , boost::mpl::iterator_range<typename boost::mpl::next<First>::type, Last>
       >
      new_array_seq;
    return create_primitive_type_descriptor
      <typename boost::mpl::begin<new_array_seq>::type
       , typename boost::mpl::end<new_array_seq>::type>
        ::length(first, last);
  }

  template <typename DescriptorFirst, typename DescriptorLast, typename T>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag<javabind::array<T> >)
  {
    return 1 + length_array_aux(first, last, tag<T>());
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag< ::jintArray>)
  {
    return length_aux(first, last, tag<javabind::array<jint> >());
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag< ::jcharArray>)
  {
    return length_aux(first, last, tag<javabind::array<jchar> >());
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag<javabind::string>)
  {
    return create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::length(first, last) + std::strlen("java/lang/String") + 2;
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag< ::jstring>)
  {
    return length_aux(first, last, tag<javabind::string>());
  }

  template <typename DescriptorFirst, typename DescriptorLast, typename T>
  static std::size_t length_aux(DescriptorFirst first, DescriptorLast last
                                , tag<T>)
  {
    return create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::length(first, last) + 1;
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

  template <typename DescriptorFirst, typename DescriptorLast>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag< ::jobject>)
  {
    run_aux(v, first, last, tag<javabind::object>());
  }

  template <typename DescriptorFirst, typename DescriptorLast, typename T>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag<array<T> >)
  {
    v[0] = '[';
    typedef boost::mpl::joint_view
      <boost::mpl::single_view<T>
       , boost::mpl::iterator_range<typename boost::mpl::next<First>::type, Last>
       >
      new_array_seq;
    return create_primitive_type_descriptor
      <typename boost::mpl::begin<new_array_seq>::type
       , typename boost::mpl::end<new_array_seq>::type>
      ::run(v + 1, first, last);
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag< ::jintArray>)
  {
    run_aux(v, first, last, tag<javabind::array<jint> >());
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag< ::jcharArray>)
  {
    run_aux(v, first, last, tag<javabind::array<jchar> >());
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag<javabind::string>)
  {
    const char* string = "java/lang/String";
    std::size_t s = std::strlen(string);
    v[0] = 'L';
    std::memcpy(v+1, string, s);
    v[s+1] = ';';
    create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
      ::run(v + s + 2, first, last);
  }

  template <typename DescriptorFirst, typename DescriptorLast>
  static void run_aux(char* v, DescriptorFirst first, DescriptorLast last
                      , tag< ::jstring>)
  {
    run_aux(v, first, last, tag<javabind::string>());
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

  // static void run(char* v)
  // {
  //   check_primitive(tag<typename boost::mpl::deref<First>::type>());
  //   v[0] = field_descriptor_traits<typename boost::mpl::deref<First>::type>::value[0];
  //   create_primitive_type_descriptor<typename boost::mpl::next<First>::type, Last>
  //     ::run(v + 1);
  // }
};

template <typename Last>
struct create_primitive_type_descriptor<Last, Last>
{
  template <typename DescriptorLast>
  static void run(char*, DescriptorLast, DescriptorLast) {}

  // static void run(char*) {}

  template <typename DescriptorLast>
  static std::size_t length(DescriptorLast, DescriptorLast) { return 0; }
};

} }

#endif

