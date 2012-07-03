// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_DETAIL_DESCRIPTORS_HPP
#define JVB_DETAIL_DESCRIPTORS_HPP

#include <jvb/type_mapping.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/for_each.hpp>

#include <algorithm>

namespace jvb { namespace detail { namespace descriptors {

template <typename T>
struct primitive_type_traits;

template <>
struct primitive_type_traits<char_>
{
  typedef boost::mpl::char_<'C'> type;
};

template <>
struct primitive_type_traits<int_>
{
  typedef boost::mpl::char_<'I'> type;
};

template <>
struct primitive_type_traits<double_>
{
  typedef boost::mpl::char_<'D'> type;
};

template <>
struct primitive_type_traits<void>
{
  typedef boost::mpl::char_<'V'> type;
};

template <>
struct primitive_type_traits<long_>
{
  typedef boost::mpl::char_<'J'> type;
};

template <>
struct primitive_type_traits<bool>
{
  typedef boost::mpl::char_<'Z'> type;
};

template <>
struct primitive_type_traits<byte>
{
  typedef boost::mpl::char_<'B'> type;
};

template <typename T, typename OutputIterator>
OutputIterator descriptor(OutputIterator iterator);

template <typename T>
struct tag
{
  typedef T type;
};

template <typename OutputIterator, typename T>
OutputIterator composite_descriptor_aux(OutputIterator iterator, tag<T>);

template <typename OutputIterator>
OutputIterator composite_descriptor_aux(OutputIterator iterator, tag<string>)
{
  const char string_descriptor[] = "Ljava/lang/String;";
  return std::copy(&string_descriptor[0], &string_descriptor[0] + (sizeof(string_descriptor)-1)
                   , iterator);
}

template <typename T, typename OutputIterator>
OutputIterator descriptor_aux(OutputIterator iterator, boost::mpl::false_)
{
  return descriptors::composite_descriptor_aux(iterator, tag<T>());
}

template <typename T, typename OutputIterator>
OutputIterator descriptor_aux(OutputIterator iterator, boost::mpl::true_)
{
  *iterator = primitive_type_traits<T>::type::value;
  return ++iterator;
}

template <typename OutputIterator>
struct descriptor_function_object
{
  descriptor_function_object(OutputIterator iterator)
    : iterator(iterator) {}

  template <typename T>
  void operator()(tag<T>) const
  {
    iterator = descriptor<T>(iterator);
  }

  mutable OutputIterator iterator;
};

struct tagger
{
  template <typename T>
  struct apply
  {
    typedef tag<T> type;
  };
};

template <typename R, typename Types, typename OutputIterator>
OutputIterator descriptor_function(OutputIterator iterator)
{
  *iterator++ = '(';
  typedef typename boost::mpl::transform<Types, tagger>::type tagged_types;
  std::cout << "descriptor_function " << typeid(tagged_types).name() << std::endl;
  typedef descriptor_function_object<OutputIterator> function_object;
  function_object f(iterator);
  boost::mpl::for_each<tagged_types>(boost::ref(f));
  *f.iterator++ = ')';
  return descriptors::descriptor<R>(f.iterator);
}

template <typename T, typename OutputIterator>
OutputIterator descriptor(OutputIterator iterator)
{
  typedef jvb::type_mapping<T> type_mapping;
  iterator = descriptor_aux<T>(iterator, typename type_mapping::is_primitive());
  return iterator;
}

} } }

#endif
