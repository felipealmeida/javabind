// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_TESTS_LOAD_FILE_CLASS_HPP
#define JAVABIND_TESTS_LOAD_FILE_CLASS_HPP

#include <boost/utility.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iterator>

javabind::class_ load_file_class(const char* filename, javabind::env env)
{
  std::cout << "Filename: " << filename << std::endl;
  std::ifstream file(filename);
  file.seekg(0, std::ios::end);
  std::size_t size = file.tellg();
  assert(size != 0);
  file.seekg(0, std::ios::beg);
  std::vector<char> buf(size);
  file.rdbuf()->sgetn(&buf[0], size);
  typedef std::reverse_iterator<const char*> iterator;
  iterator first(filename + std::strlen(filename))
    , last(filename);
  iterator filename_start = std::find(first, last, '/');
  iterator filename_end = std::find(first, last, '.');
  std::string name("javabind/tests/");
  name.insert(name.end(), filename_start.base(), boost::prior(filename_end.base()));
  std::cout << "Loading name " << name << std::endl;
  return env.define_class(name.c_str(), 0
                          , reinterpret_cast<jbyte*>(&buf[0]), size);
}

#endif
