// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_METHOD_DESCRIPTOR_HPP
#define JAVABIND_METHOD_DESCRIPTOR_HPP

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
#include <boost/fusion/container/vector.hpp>

#include <cstring>
#include <vector>

namespace javabind {

namespace method_descriptor_detail {



}

template <typename F, typename OutputIterator, typename S>
void method_descriptor(OutputIterator iterator, S s = boost::fusion::vector0<>())
{
  
}

}

#endif
