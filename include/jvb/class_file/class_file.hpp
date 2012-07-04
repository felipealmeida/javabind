// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CLASS_FILE_CLASS_HPP
#define JVB_CLASS_FILE_CLASS_HPP

namespace jvb { namespace class_files {

struct class_
{
  class_(const char* name)
    : name(name) {}

  const char* name;
};

} }

#endif
