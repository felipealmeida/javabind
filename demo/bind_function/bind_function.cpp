// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>
#include <jvb/bind_function.hpp>

#include <fstream>
#include <vector>

struct print
{
  void operator()(jvb::environment e, jvb::Object self)
  {
    std::cout << "print::operator()" << std::endl;
  }
};

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

  c = jvb::Class(env, "BindFunctionHelloWorld");

  jvb::bind_function<void(jvb::environment, jvb::Object), ::print>(env, c, "print");

  jvb::constructors<void()> constructor(env, c);
  jvb::Object object = jvb::new_<jvb::Object>(env, constructor);
  jvb::method<void()> print(env, object.raw(), "print");
  try
  {
    print(env);
  }
  catch(std::exception const& e)
  {
    env.raw()->ExceptionDescribe();
  }
}
