// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CLASS_FILE_CLASS_HPP
#define JVB_CLASS_FILE_CLASS_HPP

#include <vector>

namespace jvb { namespace class_files {

struct implemented_method
{
  
};

struct not_implemented_method
{
  const char* name;
  std::string descriptor;
};

struct field
{
  const char* name;
  std::string descriptor;
};

struct class_
{
  class_(const char* name)
    : name(name) {}

  const char* name;
  std::vector<implemented_method> implemented_methods;
  std::vector<not_implemented_method> not_implemented_methods;
  std::vector<field> static_fields;
};

} }

#endif
