// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>
#include <jvb/bind_class.hpp>
#include <jvb/bind_function.hpp>

#include <iostream>

struct hello_world
{
  hello_world()
  {
  }

  void print()
  {
    std::cout << "Hello World" << std::endl;
  }
};

struct print
{
  typedef void result_type;
  void operator()(jvb::environment e, jvb::Object obj) const
  {
    std::cout << "hey, I did" << std::endl;
  }
};

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.environment();

  using namespace jvb::bind_placeholders;

  jvb::bind_class<hello_world>
    (env, "HelloWorld"
     , method(public_, "print", &hello_world::print));

  jvb::Class c(env, "HelloWorld");

  jvb::bind_function<void(jvb::environment, jvb::Object), ::print>(env, c, "print");

  jvb::constructors<void()> constructor(env, c);
  jvb::Object object = jvb::new_<jvb::Object>(env, constructor);
  jvb::method<void()> print(env, object.raw(), "print");
  print(env);
}
