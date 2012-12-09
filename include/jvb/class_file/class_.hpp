// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CLASS_FILE_CLASS_HPP
#define JVB_CLASS_FILE_CLASS_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <vector>

namespace jvb { namespace class_files {

struct implemented_method
{
  std::string name;
  std::string descriptor;
};

typedef std::pair<std::string, std::string> name_descriptor_pair;

struct class_
{
  class_(const char* name)
    : name(name) {}
  class_() {}

  std::string name;
  std::vector<name_descriptor_pair> static_fields;
  std::vector<name_descriptor_pair> fields;
  std::vector<name_descriptor_pair> not_implemented_methods;
  std::vector<implemented_method> implemented_methods;
};

} }

BOOST_FUSION_ADAPT_STRUCT(jvb::class_files::class_
                          , 
                          (std::vector<jvb::class_files::name_descriptor_pair>, static_fields)
                          (std::vector<jvb::class_files::name_descriptor_pair>, fields)
                          (std::vector<jvb::class_files::name_descriptor_pair>, not_implemented_methods)
                          (jvb::class_files::implemented_method, implemented_methods)
                          (std::string, name)
                          )

BOOST_FUSION_ADAPT_STRUCT(jvb::class_files::implemented_method
                          ,
                          (std::string, name)
                          (std::string, descriptor)
                         )

#endif
