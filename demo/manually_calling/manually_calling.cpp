// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>

#include <fstream>
#include <vector>

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.environment();

  std::ifstream ifs("ManuallyCallingHelloWorld.class");
  ifs.seekg(0, std::ios::end);
  std::size_t size = ifs.tellg();
  assert(size != 0);
  ifs.seekg(0, std::ios::beg);
  std::vector<char> buf(size);
  ifs.rdbuf()->sgetn(&buf[0], size);
  std::cout << "Loading ManuallyCallingHelloWorld" << std::endl;
  jvb::Class c = env.raw()->DefineClass
    ("ManuallyCallingHelloWorld", 0, reinterpret_cast<jbyte*>(&buf[0]), size);
  assert(c != jvb::Class());
  std::cout << "Loaded ManuallyCallingHelloWorld" << std::endl;

  jvb::constructors<void()> constructor(env, c);
  jvb::Object object = jvb::new_<jvb::Object>(env, constructor);
  jvb::method<void()> sayHello(env, object.raw(), "sayHello");
  sayHello(env);
}
