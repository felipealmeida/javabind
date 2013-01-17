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

#include <boost/functional/value_factory.hpp>

#include <iostream>

JVB_ADAPT_CLASS((mypackage)(inner)(HelloWorld)
                , (public)
                , (methods
                   (print1, void(), nil)
                   (print2, void(), nil)
                  )
                  (constructors (HelloWorld()) // default constructor
                  )
                )

struct hello_world
{
  hello_world()
  {
    static std::size_t i = 0;
    assert(++i == 1);
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

  JVB_CREATE_CLASS(HelloWorld, hello_world, e
                  , (methods (print1, &hello_world::print<1>)
                      (print2, &hello_world::print<2>)
                    )
                    (factory_constructors (HelloWorld()
                                           , boost::value_factory<hello_world>())
                    )
                  );

  std::cout << "Instantiating HelloWorld java class" << std::endl;
  HelloWorld hello_world(e);
  std::cout << "Instantiated HelloWorld java class" << std::endl;
  hello_world.print1()(e);
  std::cout << "Called print1" << std::endl;
  hello_world.print2()(e);
  std::cout << "Called print2" << std::endl;
}
