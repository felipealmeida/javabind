// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ENVIRONMENT_HPP
#define JVB_ENVIRONMENT_HPP

#include <boost/filesystem/path.hpp>

#include <cassert>
#include <cstdlib>

#include <jni.h>

// #include <cassert>
// #include <stdexcept>
// #include <memory>

namespace jvb {

struct class_;

struct environment
{
  environment()
    : e(0)
  {
  }
  environment(JNIEnv* e)
  : e(e)
  {
    assert(e != 0);
  }

  class_ load_class(boost::filesystem::path path
                    , std::string const& class_name);

  class_ define_class(const char* name, jobject classloader, jbyte* buf
                        , std::size_t size) const;

  bool exception_pending() const
  {
    return e->ExceptionCheck();
  }

  JNIEnv* raw() const { return e; }
private:
  JNIEnv* e;
};

}

#endif
