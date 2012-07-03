// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>
#include <jvb/bind_function.hpp>

#include <fstream>
#include <vector>

void print()
{
}

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.environment();

  std::ifstream ifs("BindFunctionHelloWorld.class");
  ifs.seekg(0, std::ios::end);
  std::size_t size = ifs.tellg();
  assert(size != 0);
  ifs.seekg(0, std::ios::beg);
  std::vector<char> buf(size);
  ifs.rdbuf()->sgetn(&buf[0], size);
  std::cout << "Loading BindFunctionHelloWorld" << std::endl;
  jvb::Class c = env.raw()->DefineClass
    ("BindFunctionHelloWorld", 0, reinterpret_cast<jbyte*>(&buf[0]), size);
  assert(c != jvb::Class());

  jvb::bind_function(c, "print", &::print);
}
