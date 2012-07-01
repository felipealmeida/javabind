// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JVB_ERROR_HPP
#define JVB_JVB_ERROR_HPP

#include <stdexcept>

#ifndef JVB_DISABLE_BOOST_EXCEPTION
#include <boost/exception/all.hpp>
#endif

namespace jvb {

struct jvb_error
#ifndef JVB_DISABLE_BOOST_EXCEPTION
  : boost::exception, std::exception
#else
  : std::runtime_error
#endif
{
  jvb_error()
#ifndef JVB_DISABLE_BOOST_EXCEPTION
    : w("jvb::jvb_error")
#else
    : runtime_error("")
#endif
  {}
  jvb_error(const char* w)
#ifndef JVB_DISABLE_BOOST_EXCEPTION
    : w(w)
#else
    : runtime_error(w)
#endif
  {}

#ifndef JVB_DISABLE_BOOST_EXCEPTION
  const char* what() const throw()
  {
    return w;
  }

  const char* w;
#endif
};

}

#endif
