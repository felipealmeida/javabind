// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/detail/overload_set.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/push_back.hpp>

namespace mpl = boost::mpl;
typedef mpl::vector<void(jvb::string, int, jvb::string, int)
                    , void(int, jvb::string, int, jvb::string)>
sigs;
typedef jvb::detail::convertible_overloads_for_all<sigs>::type types;
typedef mpl::vector
<
    mpl::vector<jvb::environment, jvb::string, int, jvb::string, int>
  , mpl::vector<jvb::environment, const char*, int, jvb::string, int>
  , mpl::vector<jvb::environment, jvb::string, int, const char*, int>
  , mpl::vector<jvb::environment, const char*, int, const char*, int>
  , mpl::vector<jvb::environment, int, jvb::string, int, jvb::string>
  , mpl::vector<jvb::environment, int, const char*, int, jvb::string>
  , mpl::vector<jvb::environment, int, jvb::string, int, const char*>
  , mpl::vector<jvb::environment, int, const char*, int, const char*>
  > result_types;
struct comparison
{
  template <typename A0, typename A1>
  struct apply : mpl::equal<A0, A1>
  {};
};
typedef mpl::transform<types, mpl::copy<mpl::_1, mpl::back_inserter<mpl::vector0<> > >
                       , mpl::back_inserter<mpl::vector0<> > >::type normalized_types;
BOOST_MPL_ASSERT((mpl::equal<normalized_types, result_types, comparison>));
