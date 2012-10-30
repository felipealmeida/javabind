// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <jvb/jvb.hpp>
#include <jvb/adapt_class.hpp>

#include <fstream>
#include <vector>

JVB_ADAPT_CLASS((ManuallyAttribute)
                , public
                , (attributes (x, jvb::int_)))

int main()
{
  jvb::jvm jvm;
  jvb::environment env = jvm.environment();

  std::ifstream ifs("ManuallyAttribute.class");
  ifs.seekg(0, std::ios::end);
  std::size_t size = ifs.tellg();
  assert(size != 0);
  ifs.seekg(0, std::ios::beg);
  std::vector<char> buf(size);
  ifs.rdbuf()->sgetn(&buf[0], size);
  std::cout << "Loading ManuallyAttribute" << std::endl;
  jvb::Class c = env.raw()->DefineClass
    ("ManuallyAttribute", 0, reinterpret_cast<jbyte*>(&buf[0]), size);
  assert(c != jvb::Class());
  std::cout << "Loaded ManuallyAttribute" << std::endl;

  ManuallyAttribute manually_attribute
    = jvb::new_<ManuallyAttribute>(env);

  manually_attribute.x(env) = 5;
  assert(manually_attribute.x(env) == jvb::int_(5));
  manually_attribute.x(env) = 10;
  assert(manually_attribute.x(env) == jvb::int_(10));
}
