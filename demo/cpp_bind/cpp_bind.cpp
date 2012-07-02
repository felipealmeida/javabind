// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>

#include <fstream>
#include <vector>

struct CppBindHelloWorld_class : jvb::Class
{
  CppBindHelloWorld_class(jvb::environment e, jvb::Class const& cls)
    : jvb::Class(cls), constructor(e, cls)
  {}

  jvb::constructors<void()> constructor;
};

struct CppBindHelloWorld : jvb::Object
{
  CppBindHelloWorld(jvb::environment e, jobject obj)
    : jvb::Object(e, obj), sayHello(e, raw(), "sayHello")
  {}

  jvb::method<void()> sayHello;
};

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

  CppBindHelloWorld_class hello_world_class(env, c);
  // jvb::ref<CppBindHelloWorld> hello_world = jvb::new_<CppBindHelloWorld>
  //   (env, hello_world_class.constructor);
}
