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

int main()
{
  jvb::jvm jvm;
  jvb::environment e = jvm.environment();

  using namespace jvb::bind_placeholders;

  jvb::Class c = jvb::bind_class<hello_world>
    (e, "HelloWorld"
     , (
        method(public_, "print", &hello_world::print)
       ));

  // jvb::bind_function<void(jvb::environment, jvb::Object), ::print>(env, c, "print");

  jvb::constructors<void()> constructor(e, c);
  jvb::Object object = jvb::new_<jvb::Object>(e, constructor);
  jvb::method<void()> print(e, object.raw(), "print");
  print(e);
}
