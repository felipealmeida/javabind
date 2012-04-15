// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_ENV_HPP
#define JAVABIND_ENV_HPP

#include <javabind/class.hpp>
#include <javabind/string.hpp>

#include <boost/function_types/parameter_types.hpp>
#include <boost/function.hpp>

#include <boost/mpl/pop_front.hpp>

#include <jni.h>

#include <cassert>
#include <stdexcept>
#include <memory>

namespace javabind {

struct env
{
  env()
    : e(0)
  {
  }
  env(JNIEnv* e)
  : e(e)
  {
    assert(e != 0);
  }

  class_ find_class(const char* name) const
  {
    jclass cls = e->FindClass(name);
    if(cls == 0)
      throw std::runtime_error("Couldn't find class");
    return class_(cls, e);
  }
  class_ find_class(std::string const& name) const { return find_class(name.c_str()); }

  string create_string_utf(const char* s)
  {
    return string(e->NewStringUTF(s), e);
  }

  class_ define_class(const char* name, jobject classloader, jbyte* buf, std::size_t size) const
  {
    jclass c = e->DefineClass(name, classloader, buf, size);
    if(c == 0)
      throw std::runtime_error("Couldn't define class");
    return class_(c, e);
  }

  bool exception_pending() const
  {
    return e->ExceptionCheck();
  }

  // template <typename F>
  // void register_method(const char* name, javabind::class_ cls, F f)
  // {
  //   typedef typename boost::function_types::parameter_types<F>::type
  //     parameter_types;
  //   BOOST_MPL_ASSERT_RELATION(boost::mpl::size<parameter_types>::type::value, >=, 1);
  //   register_method(name, cls, f
  //                   , detail::tag
  //                   <typename boost::mpl::deref
  //                    <typename boost::mpl::begin<parameter_types>::type>::type>());
  // }

  // struct bootstrap_info
  // {
  //   field<jlong> peer;
  //   boost::function<void(javabind::object)> f;
  // };  

//   void register_methods(const char* name, javabind::class_ cls
//                         , boost::function<void(javabind::object)> 
//                         f = boost::function<void(javabind::object)>)
//   {
//     std::auto_ptr<bootstrap_info> info (new bootstrap_info);
//     info->peer = cls.field<jlong>("peer");
//     info->f = f;
//     static_field<jlong> bootstrap = cls.static_field<jlong>("bootstrap");
//     bootstrap.set(cls, reinterpret_cast<jlong>(static_cast<void*>(info.release())));

//     char signature[] = "(J)V";
//     JNINativeMethod method = {const_cast<char*>(name), signature
//                               , reinterpret_cast<void*>(&env::registered_init_method)};
//     if(e->RegisterNatives(cls.raw(), &method, 1) < 0)
//     {
//       throw std::runtime_error("Error registering method");
//     }
//   }
// private:
//   struct peer_info
//   {
    
//   };

//   static void registered_init_method(JNIEnv* env, jobject self_internal, jlong l)
//   {
//     std::cout << "Registered init method" << std::endl;
//     std::cout << "bootstrap l " << l << std::endl;

//     if(l)
//     {
//       javabind::object self(self_internal, env);
//       bootstrap_info* info = static_cast<bootstrap_info*>
//         (reinterpret_cast<void*>(l));

//       assert(info->peer.get(self) == 0);

      
//     }
//   }

//   static void registered_object_method(JNIEnv* env, jobject self)
//   {
//     std::cout << "registered_object_method" << std::endl;
//   }

//   template <typename F>
//   void register_method(const char* name
//                        , javabind::class_ cls, F f, detail::tag<javabind::object>)
//   {
//     typedef typename boost::function_types::parameter_types<F>::type
//       extended_parameter_types;
//     typedef typename boost::mpl::pop_front<extended_parameter_types>::type parameter_types;
//     char signature[boost::mpl::size<parameter_types>::type::value+4];
//     signature[0] = '(';
//     signature[sizeof(signature)-3] = ')';
//     signature[sizeof(signature)-2] = field_descriptor_traits      
//       <typename boost::function_types::result_type<F>::type>::value[0];
//     signature[sizeof(signature)-1] = 0;
//     detail::create_primitive_type_descriptor
//       <typename boost::mpl::begin<parameter_types>::type
//        , typename boost::mpl::end<parameter_types>::type>::run(signature+1);
//     std::cout << "signature: " << signature << std::endl;
//     JNINativeMethod method = {const_cast<char*>(name), signature
//                               , reinterpret_cast<void*>(&env::registered_object_method)};
//     if(e->RegisterNatives(cls.raw(), &method, 1) < 0)
//     {
//       throw std::runtime_error("Error registering method");
//     }
//   }

//   template <typename F>
//   void register_method(const char* name
//                        , javabind::class_ cls, F f, detail::tag<javabind::class_>)
//   {
//     std::cout << "Static" << std::endl;
//   }

  JNIEnv* e;
};

}

#endif
