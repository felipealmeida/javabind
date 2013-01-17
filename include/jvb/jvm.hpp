// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_JVM_HPP
#define JVB_JVM_HPP

#include <jvb/keywords.hpp>
#include <jvb/error.hpp>
#include <jvb/environment.hpp>
#include <jvb/class.hpp>

#include <boost/parameter.hpp>

#include <fstream>

namespace jvb {

struct jvm_impl
{
  struct destroy_jvm
  {
    void operator()(JavaVM* vm) const
    {
      std::cout << "Destroy JVM" << std::endl;
      vm->DestroyJavaVM();
    }
  };
  struct null_deleter
  {
      constexpr void operator()(JavaVM *vm) const noexcept {}
  };

  template <typename ParameterPack>
  jvm_impl(ParameterPack args)
  {
    std::cout << "Creating JVM" << std::endl;
    JavaVMInitArgs vm_args;
    std::memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = 0x00010002;
    vm_args.ignoreUnrecognized = JNI_TRUE;
    JavaVMOption options[9];
    options[0].optionString = const_cast<char*>("-Xbatch");
    options[1].optionString = const_cast<char*>("-Xrs");
    options[2].optionString = const_cast<char*>("-Xcheck:jni");
    options[3].optionString = const_cast<char*>("-Xfuture");
    options[4].optionString = const_cast<char*>("-Xint");
    // options[5].optionString = const_cast<char*>("-verbose"); // crashes with DefineClass with JNI in JDK 7u9
    options[5].optionString = const_cast<char*>("-esa");
    vm_args.options = options;
    vm_args.nOptions = 6;

    JNIEnv* env;
    JavaVM* jvm;
    int res = JNI_CreateJavaVM(&jvm, &env, &vm_args);
    if(!(res >= 0))
      JVB_THROW_EXCEPTION(jvb_error());
    else
      jvm_ = boost::shared_ptr<JavaVM>(jvm, destroy_jvm());
  }
  jvm_impl(JavaVM* jvm)
    : jvm_(jvm, null_deleter{}) {}
  jvb::environment environment() const
  {
    JNIEnv* env = 0;
    jvm_->AttachCurrentThread(&env, 0);
    return jvb::environment(env);
  }

private:
  boost::shared_ptr<JavaVM> jvm_;
};

struct jvm : jvm_impl
{
  BOOST_PARAMETER_CONSTRUCTOR
  (jvm, (jvm_impl), keywords::tag
   , (optional
      (check_jni, (bool))
     )
  )
  jvm(JavaVM* jvm_)
    : jvm_impl(jvm_) {}
};

}

#endif
