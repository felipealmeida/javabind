// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>
#include <jvb/bind_class.hpp>
#include <jvb/bind_function.hpp>
#include <jvb/define_class.hpp>

#include <iostream>

JVB_DEFINE_CLASS((HelloWorld)
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

  jvb::Class c = jvb::bind_class<hello_world>
    (e, "HelloWorld"
     , (
        method(public_, "print1", &hello_world::print<1>)
        , method(public_, "print2", &hello_world::print<2>)
        ));

  jvb::constructors<void()> constructor(e, c);
  jvb::Object object = jvb::new_<jvb::Object>(e, constructor);
  jvb::method<void()> print1(e, object.raw(), "print1");
  print1(e);
  jvb::method<void()> print2(e, object.raw(), "print2");
  print2(e);
}
