// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>
#include <jvb/bind_class.hpp>
#include <jvb/bind_function.hpp>
#include <jvb/adapt_class.hpp>
#include <jvb/create_class.hpp>

#include <iostream>

JVB_ADAPT_CLASS((mypackage)(HelloWorld)
                , (public)
                , (methods (print1, void())(print2, void())))

struct hello_world
{
  hello_world()
  {
    std::cout << "hello_world::hello_world" << std::endl;
  }

  template <int N>
  void print()
  {
    std::cout << "hello_world::print Hello World " << N << std::endl;
  }
};

int main()
{
  jvb::jvm jvm;
  jvb::environment e = jvm.environment();

  using namespace jvb::bind_placeholders;

  JVB_CREATE_CLASS(HelloWorld, hello_world, e
                  , (methods (print1, &hello_world::print<1>)
                      (print2, &hello_world::print<2>)));

  HelloWorld hello_world = jvb::new_<HelloWorld>(e);
  hello_world.print1()(e);
  hello_world.print2()(e);
}
