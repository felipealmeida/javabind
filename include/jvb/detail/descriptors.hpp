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
#include <boost/type_traits/is_fundamental.hpp>

#include <algorithm>
#include <iostream>
#include <typeinfo>

namespace jvb { namespace detail { namespace descriptors {

template <typename T, typename Enable = void>
struct primitive_type_traits;

template <>
struct primitive_type_traits<char_>
{
  typedef boost::mpl::char_<'C'> type;
};

template <>
struct primitive_type_traits<short_>
{
  typedef boost::mpl::char_<'S'> type;
};

template <>
struct primitive_type_traits<float_>
{
  typedef boost::mpl::char_<'F'> type;
};

template <>
struct primitive_type_traits<double_>
{
  typedef boost::mpl::char_<'D'> type;
};

template <>
struct primitive_type_traits<int_>
{
  typedef boost::mpl::char_<'I'> type;
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

template <typename T>
struct primitive_type_traits<T, typename boost::enable_if<boost::is_pointer<T> >::type>
{
  typedef boost::mpl::char_<'J'> type;
};

template <typename T, typename OutputIterator>
OutputIterator descriptor(jvb::environment e, OutputIterator iterator);

template <typename T>
struct tag
{
  typedef T type;
};

template <typename OutputIterator, typename T>
OutputIterator composite_descriptor_user_defined(jvb::environment e, OutputIterator iterator, tag<T>)
{
  const char* name = T::name();
  *iterator++ = 'L';
  iterator = std::copy(name, name + T::name_size, iterator);
  *iterator++ = ';';
  return iterator;
}

template <typename OutputIterator, typename T>
OutputIterator composite_descriptor_aux(jvb::environment e, OutputIterator iterator, tag<T> t)
{
  BOOST_MPL_ASSERT((mpl::not_<boost::is_fundamental<T> >));
  return composite_descriptor_user_defined(e, iterator, t);
}

template <typename OutputIterator>
OutputIterator composite_descriptor_aux(jvb::environment e, OutputIterator iterator, tag<string>)
{
  const char string_descriptor[] = "Ljava/lang/String;";
  return std::copy(&string_descriptor[0], &string_descriptor[0] + (sizeof(string_descriptor)-1)
                   , iterator);
}

template <typename OutputIterator, typename T>
OutputIterator composite_descriptor_aux(jvb::environment e, OutputIterator iterator, tag<array<T> >)
{
  *iterator++ = '[';
  return descriptor<T>(e, iterator);
}

template <typename T, typename OutputIterator>
OutputIterator descriptor_aux(jvb::environment e, OutputIterator iterator, boost::mpl::false_)
{
  return descriptors::composite_descriptor_aux(e, iterator, tag<T>());
}

template <typename T, typename OutputIterator>
OutputIterator descriptor_aux(jvb::environment e, OutputIterator iterator, boost::mpl::true_)
{
  *iterator = primitive_type_traits<T>::type::value;
  return ++iterator;
}

template <typename OutputIterator>
struct descriptor_function_object
{
  descriptor_function_object(jvb::environment e, OutputIterator iterator)
    : e(e), iterator(iterator) {}

  template <typename T>
  void operator()(tag<T>) const
  {
    iterator = descriptor<T>(e, iterator);
  }

  jvb::environment e;
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
OutputIterator descriptor_function(jvb::environment e, OutputIterator iterator)
{
  *iterator++ = '(';
  typedef typename boost::mpl::transform<Types, tagger>::type tagged_types;
  std::cout << "descriptor_function " << typeid(tagged_types).name() << std::endl;
  typedef descriptor_function_object<OutputIterator> function_object;
  function_object f(e, iterator);
  boost::mpl::for_each<tagged_types>(boost::ref(f));
  *f.iterator++ = ')';
  return descriptors::descriptor<R>(e, f.iterator);
}

template <typename T, typename OutputIterator>
OutputIterator descriptor(jvb::environment e, OutputIterator iterator)
{
  typedef jvb::type_mapping<T> type_mapping;
  iterator = descriptor_aux<T>(e, iterator, typename type_mapping::is_primitive());
  return iterator;
}

} } }

#endif
