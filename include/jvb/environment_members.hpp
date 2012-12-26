// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_ENVIRONMENT_MEMBERS_HPP
#define JVB_ENVIRONMENT_MEMBERS_HPP

#include <jvb/environment.hpp>
#include <jvb/error.hpp>
#include <jvb/class.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

namespace jvb {

inline class_ environment::define_class(const char* name, jobject classloader, jbyte* buf
                                        , std::size_t size) const
{
  jclass c = e->DefineClass(name, classloader, buf, size);
  if(c == 0) error::throw_exception(*this);
  return class_(c);
}

inline class_ environment::load_class(boost::filesystem::path path
                                      , std::string const& class_name)
{
  boost::filesystem::ifstream file(path);
  file.seekg(0, std::ios::end);
  std::size_t size = file.tellg();
  assert(size != 0);
  file.seekg(0, std::ios::beg);
  std::vector<char> buf(size);
  file.rdbuf()->sgetn(&buf[0], size);
  return define_class(class_name.c_str(), 0
                      , reinterpret_cast<jbyte*>(&buf[0]), size);
}

}

#endif
