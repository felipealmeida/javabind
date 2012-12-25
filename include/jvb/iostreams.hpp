// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_IOSTREAMS_HPP
#define JVB_IOSTREAMS_HPP

#include <jvb/environment.hpp>
#include <jvb/object.hpp>
#include <jvb/string.hpp>

#include <ostream>

namespace jvb {

template <typename T>
struct ostream_wrapper : std::pair<environment, T>
{
  ostream_wrapper(environment e, T obj)
    : std::pair<environment, T>(e, obj) {}
};

template <typename T>
ostream_wrapper<T> ostream_wrap(environment e, T obj)
{
  return ostream_wrapper<T>(e, obj);
}

inline std::ostream& operator<<(std::ostream& os, ostream_wrapper<string> s)
{
  std::ostream::sentry sentry(os);

  const char* str = s.first.raw()->GetStringUTFChars(s.second.raw(), 0);
  if(str)
  {
    os << str;
    s.first.raw()->ReleaseStringUTFChars(s.second.raw(), str);
    return os;
  }
  else
    return os << "[allocation error while returning string]";
}

template <typename T>
inline
typename boost::enable_if
<boost::is_base_of<jvb::object, T>
 , std::ostream&>::type
operator<<(std::ostream& os, ostream_wrapper<T> o)
{
  return os << ostream_wrap(o.first, o.second.to_string(o.first));
}

}

#endif
