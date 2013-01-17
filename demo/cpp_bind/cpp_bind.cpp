// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>

#include <fstream>
#include <vector>

JVB_ADAPT_CLASS((CppBindHelloWorld)
                , (public)
                , (methods
                   (sayHello, void(), nil)
                  )
                  (constructors
                   (CppBindHelloWorld())
                  )
               )

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.environment();

  std::ifstream ifs("CppBindHelloWorld.class");
  ifs.seekg(0, std::ios::end);
  std::size_t size = ifs.tellg();
  assert(size != 0);
  ifs.seekg(0, std::ios::beg);
  std::vector<char> buf(size);
  ifs.rdbuf()->sgetn(&buf[0], size);
  std::cout << "Loading CppBindHelloWorld" << std::endl;
  jvb::Class c = env.raw()->DefineClass
    ("CppBindHelloWorld", 0, reinterpret_cast<jbyte*>(&buf[0]), size);
  assert(c != jvb::Class());

  CppBindHelloWorld hello_world(env);
  hello_world.sayHello()(env);
}
