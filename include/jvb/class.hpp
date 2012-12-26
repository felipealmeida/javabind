// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CLASS_HPP
#define JVB_CLASS_HPP

#include <jvb/environment.hpp>

#include <jni.h>

#include <string>
#include <algorithm>

#include <stdexcept>
#include <iostream>
#include <vector>
#include <iterator>

namespace jvb {

struct class_
{
  class_() : cls(0) {}
  class_(environment e, const char* name)
    : cls(e.raw()->FindClass(name))
  {
    assert(cls != 0);
  }
  class_(jclass cls)
    : cls(cls)
  {
  }

  typedef ::jclass java_type;

//   template <typename F>
//   jvb::method<F> method(const char* name) const
//   {
//     return this->template method<F>(name, boost::fusion::vector0<>());
//   }

//   template <typename F, typename S>
//   jvb::method<F> method(const char* name, S s) const
//   {
//     typedef typename boost::function_types::parameter_types<F>::type
//       parameter_types;

//     typedef typename boost::function_types::result_type<F>::type result_type;
//     typedef boost::mpl::single_view<result_type> result_type_sequence;
//     typedef detail::create_primitive_type_descriptor
//       <typename boost::mpl::begin<result_type_sequence>::type
//        , typename boost::mpl::end<result_type_sequence>::type> result_type_descriptor;
//     typedef detail::split_descriptors<result_type_descriptor> split_descriptors_type;
//     typename split_descriptors_type::template my_result<S>::type
//       sequences = split_descriptors_type::split(s);

//     typedef detail::create_primitive_type_descriptor
//       <typename boost::mpl::begin<parameter_types>::type
//        , typename boost::mpl::end<parameter_types>::type> create_descriptor;

//     std::size_t parameters_length = create_descriptor::length
//       (boost::fusion::begin(sequences.second), boost::fusion::end(sequences.second));
//     std::cout << "parameters_length: " << parameters_length << std::endl;

//     std::vector<char> type
//       (parameters_length + result_type_descriptor::length
//         (boost::fusion::begin(sequences.first), boost::fusion::end(sequences.first))
//         +3);
//     type[0] = '(';
//     type[parameters_length+1] = ')';
//     type[type.size()-1] = 0;
//     create_descriptor::run(&type[1], boost::fusion::begin(sequences.second)
//                            , boost::fusion::end(sequences.second));
//     result_type_descriptor::run(&type[parameters_length+2]
//                                 , boost::fusion::begin(sequences.first)
//                                 , boost::fusion::end(sequences.first));
//     assert(type[type.size()-1] == 0);
//     std::cout << "S Using as type: " << &type[0] << std::endl;
//     jmethodID id = env->GetMethodID(cls, name, &type[0]);
//     if(id == 0)
//       throw std::runtime_error("Couldn't find method");
//     return jvb::method<F>(id);
//   }

//   template <typename F>
//   jvb::method<F> method(const char* name, const char* d) const
//   {
//     return method<F>(name, jvb::descriptors(d));
//   }

//   template <typename F>
//   jvb::static_method<F> static_method(const char* name) const
//   {
//     return this->template static_method<F>(name, boost::fusion::vector0<>());
//   }

//   template <typename F, typename S>
//   jvb::static_method<F> static_method(const char* name, S s) const
//   {
//     typedef typename boost::function_types::parameter_types<F>::type
//       parameter_types;
//     typedef detail::create_primitive_type_descriptor
//       <typename boost::mpl::begin<parameter_types>::type
//        , typename boost::mpl::end<parameter_types>::type> create_descriptor;
//     std::vector<char> type
//       (create_descriptor::length
//        (boost::fusion::begin(s)
//         , boost::fusion::end(s))+4);
//     type[0] = '(';
//     type[type.size()-3] = ')';
//     type[type.size()-2] = field_descriptor_traits
//       <typename boost::function_types::result_type<F>::type>::value[0];
//     create_descriptor::run(&type[1], boost::fusion::begin(s), boost::fusion::end(s));
//     type[type.size()-1] = 0;
//     std::cout << "S Using as type: " << &type[0] << std::endl;
//     jmethodID id = env->GetStaticMethodID(cls, name, &type[0]);
//     if(id == 0)
//       throw std::runtime_error("Couldn't find method");
//     return jvb::static_method<F>(id, env);
//   }

//   template <typename F>
//   jvb::static_method<F> static_method(const char* name, const char* d) const
//   {
//     return static_method<F>(name, jvb::descriptors(d));
//   }

//   template <typename F>
//   jvb::constructor<F> constructor() const
//   {
//     return this->template constructor<F>(boost::fusion::vector0<>());
//   }

//   template <typename F, typename S>
//   jvb::constructor<F> constructor(S s) const
//   {
//     typedef typename boost::function_types::parameter_types<F>::type
//       parameter_types;
//     typedef detail::create_primitive_type_descriptor
//       <typename boost::mpl::begin<parameter_types>::type
//        , typename boost::mpl::end<parameter_types>::type> create_descriptor;
//     std::vector<char> type
//       (create_descriptor::length
//        (boost::fusion::begin(s)
//         , boost::fusion::end(s))+4);
//     type[0] = '(';
//     type[type.size()-3] = ')';
//     type[type.size()-2] = 'V';
//     type[type.size()-1] = 0;
//     create_descriptor::run(&type[1], boost::fusion::begin(s), boost::fusion::end(s));
//     std::cout << "C Using as type: " << &type[0] << std::endl;
//     jmethodID id = env->GetMethodID(cls, "<init>", &type[0]);
//     if(id == 0)
//       throw std::runtime_error("Couldn't find method");
//     return jvb::constructor<F>(id);
//   }

//   template <typename F>
//   jvb::constructor<F> constructor(const char* descriptor) const
//   {
//     return this->constructor<F>(descriptors(descriptor));
//   }

//   template <typename T>
//   jvb::static_field<T> find_static_field(const char* name) const
//   {
//     jfieldID id = env->GetStaticFieldID(cls, name, field_descriptor_traits<T>::value);
//     if(id == 0)
//       throw std::runtime_error("Couldn't find field");
//     return jvb::static_field<T>(id);
//   }

//   template <typename T>
//   jvb::static_field<T> find_static_field(const char* name, const char* type) const
//   {
//     jfieldID id = env->GetStaticFieldID(cls, name, type);
//     if(id == 0)
//       throw std::runtime_error("Couldn't find field");
//     return jvb::static_field<T>(id);
//   }

//   template <typename T>
//   jvb::field<T> find_field(const char* name) const
//   {
//     jfieldID id = env->GetFieldID(cls, name, field_descriptor_traits<T>::value);
//     if(id == 0)
//       throw std::runtime_error("Couldn't find field");
//     return jvb::field<T>(id);
//   }

//   template <typename T>
//   jvb::field<T> find_field(const char* name, const char* type) const
//   {
//     jfieldID id = env->GetFieldID(cls, name, type);
//     if(id == 0)
//       throw std::runtime_error("Couldn't find field");
//     return jvb::field<T>(id);
//   }

  ::jclass raw() const { return cls; }
  std::string name(environment e) const
  {
    jclass cls1 = e.raw()->GetObjectClass(cls);
    assert(cls1 != 0);
    jmethodID get_name_id = e.raw()->GetMethodID(cls1, "getName", "()Ljava/lang/String;");
    assert(get_name_id != 0);
    jstring name_string = static_cast<jstring>
      (static_cast<void*>
       (e.raw()->CallObjectMethod(cls, get_name_id)));
    assert(name_string != 0);
    const char* name = e.raw()->GetStringUTFChars(name_string, 0);
    assert(name != 0);
    std::string n(name);
    std::replace(n.begin(), n.end(), '.', '/');
    e.raw()->ReleaseStringUTFChars(name_string, name);
    return n;
  }
private:
  ::jclass cls;
  
};

inline bool operator==(class_ const& lhs, class_ const& rhs)
{
  return lhs.raw() == rhs.raw();
}
inline bool operator!=(class_ const& lhs, class_ const& rhs)
{
  return !(lhs == rhs);
}

typedef class_ Class;

namespace jcl { namespace java { namespace lang {

typedef jvb::class_ Class;

} } }

}

#endif
