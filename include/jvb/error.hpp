// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ERROR_HPP
#define JVB_ERROR_HPP

#include <jvb/jvb_error.hpp>
#include <jvb/detail/hidden_object.hpp>

#include <boost/system/error_code.hpp>

#ifndef JVB_DISABLE_BOOST_EXCEPTION
#define JVB_THROW_EXCEPTION(x) BOOST_THROW_EXCEPTION(x)
#else
#define JVB_THROW_EXCEPTION(x) throw x
#endif

namespace jvb {

namespace jcl { namespace java { namespace lang {

struct Throwable;

} } }

struct thrown_error : jvb_error
{
  thrown_error(jthrowable throwable)
    : throwable(throwable) {}

  const char* what() const throw()
  {
    return "thrown_error";
  }

  jcl::java::lang::Throwable exception() const;

private:
  jthrowable throwable;
};

namespace error {

enum errors
{
  exception_thrown
};

} }

namespace boost { namespace system {

template <> struct is_error_code_enum<jvb::error::errors>
{
  static const bool value = true;
};

} }

namespace jvb { namespace error {

struct jvb_error_category : boost::system::error_category
{
  ~jvb_error_category();
  const char* name() const;
  std::string message(int ev) const;
};

inline jvb_error_category::~jvb_error_category() {}

inline const char* jvb_error_category::name() const
{
  return "jvb_error_category";
}

inline std::string jvb_error_category::message(int ev) const
{
  return "jvb_error_category";
}

inline jvb_error_category const& get_error_category()
{
  static const jvb_error_category error_category;
  return error_category;
}

namespace {

jvb_error_category const& error_category = get_error_category();

}

inline boost::system::error_code make_error_code(errors e)
{
  int e_ = e;
  return boost::system::error_code(e_, error_category);
}

inline void throw_exception(environment e)
{
  if(e.exception_pending())
  {
    jthrowable ex = e.raw()->ExceptionOccurred();
    e.raw()->ExceptionClear();
    JVB_THROW_EXCEPTION(thrown_error(ex));
  }
}

} }

#endif

