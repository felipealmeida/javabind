// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JAVABIND_REGISTER_CLASS_HPP
#define JAVABIND_REGISTER_CLASS_HPP

#include <javabind/reg/class.hpp>
#include <javabind/field.hpp>
#include <javabind/detail/wrapper_native.hpp>
#include <javabind/detail/wrapper_static_native.hpp>
#include <javabind/detail/bootstrap_info.hpp>
#include <javabind/detail/peer_info.hpp>
#include <javabind/reg/extends.hpp>
#include <javabind/reg/object.hpp>
#include <javabind/detail/function_safe_cast.hpp>
#include <javabind/detail/split_descriptors.hpp>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/if.hpp>

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>

#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>

#include <boost/type_traits/remove_reference.hpp>

#include <vector>
#include <list>

namespace javabind { namespace detail {

template <typename T, typename S, typename C>
void native_init_handler(JNIEnv* env, jobject obj_internal, jlong bootstrap)
{
  try
  {
    std::cout << "native_init_handler" << std::endl;
    javabind::object obj(obj_internal, env);
    bootstrap_info* info = reinterpret_cast<bootstrap_info*>(bootstrap);
    assert(info->peer.get(obj) == 0);
    bootstrap_info_derived<S, C>* d = static_cast<bootstrap_info_derived<S, C>*>(info);

    reg::object_info oinfo = {d->peer, env->NewWeakGlobalRef(obj_internal)};

    peer_info<T>* peer = new peer_info<T>(info, d->c, env, oinfo);
    assert(peer != 0);
    info->peer.set(obj, reinterpret_cast<jlong>(peer));
    assert(info->peer.get(obj) == reinterpret_cast<jlong>(peer));
    std::cout << "native_init_handler finished successful" << std::endl;
  }
  catch(std::exception& e)
  {
    std::cout << "A exception was catched in native_init_handler" << std::endl;
  }
}

template <typename T, typename S, typename C>
void native_init_handler_with_extends(JNIEnv* env, jobject obj_internal, jlong bootstrap)
{
  try
  {
    std::cout << "native_init_handler" << std::endl;
    javabind::object obj(obj_internal, env);
    bootstrap_info* info = reinterpret_cast<bootstrap_info*>(bootstrap);
    assert(info->peer.get(obj) == 0);
    bootstrap_info_derived_with_extends<S, C>* 
      d = static_cast<bootstrap_info_derived_with_extends<S, C>*>(info);

    reg::object_info oinfo = {d->peer, env->NewWeakGlobalRef(obj_internal)};
    reg::extends_adl_protect::extends_info extends_info
      = {d->extends_peer.raw(), env->NewWeakGlobalRef(obj_internal)};

    peer_info<T>* peer = new peer_info<T>(info, d->c, env, oinfo, extends_info);
    assert(peer != 0);
    info->peer.set(obj, reinterpret_cast<jlong>(peer));
    assert(info->peer.get(obj) == reinterpret_cast<jlong>(peer));
    std::cout << "native_init_handler finished successful" << std::endl;
  }
  catch(std::exception& e)
  {
    std::cout << "A exception was catched in native_init_handler" << std::endl;
  }
}

template <typename T>
struct initialize_native_method
{
  initialize_native_method(JNINativeMethod* methods
                           , std::list<std::vector<char> >& signatures_buffer)
    : methods(methods), signatures_buffer(signatures_buffer) {}

  template <typename F>
  struct result
  {
    typedef typename boost::mpl::deref
    <typename boost::mpl::begin
     <typename boost::function_types::parameter_types<F>::type>::type>::type first_type;
    typedef typename boost::remove_reference<first_type>::type increment_type;
    typedef boost::mpl::size_t<increment_type::type::value+1> type;
  };

  template <std::size_t index, typename Sig, typename F, bool is_static, typename S>
  boost::mpl::size_t<index+1> operator()
  (boost::mpl::size_t<index>
   , reg::function_entry<Sig, F, is_static, S> const& entry) const
  {
    typedef typename boost::function_types::parameter_types<Sig>::type
      parameter_types;
    typedef typename boost::function_types::result_type<Sig>::type
      result_type;
    typedef typename boost::mpl::if_c
      <!is_static
       , typename boost::mpl::pop_front<parameter_types>::type
       , parameter_types>::type tmp_jni_parameter_types;
    typedef typename boost::is_same
      <
        typename boost::mpl::deref
        <
          typename boost::mpl::begin<tmp_jni_parameter_types>::type
        >::type
        , JNIEnv*
      >::type has_env_first_parameter;
    typedef typename boost::mpl::if_
      <has_env_first_parameter
       , typename boost::mpl::pop_front<tmp_jni_parameter_types>::type
       , tmp_jni_parameter_types>::type jni_parameter_types;
    typedef typename boost::mpl::push_front // jlong peer
      <jni_parameter_types, long_>::type signature_parameter_types;
    typedef detail::wrapper_native_cast
      <result_type, signature_parameter_types
       , boost::function_types::is_member_function_pointer<Sig>::type::value
       , has_env_first_parameter::type::value
       , is_static>
      wrapper_native_cast;
    typedef typename wrapper_native_cast::result_type function_type;
    std::cout << "parameter_types: " << typeid(parameter_types).name() << std::endl;
    std::cout << "function_type: " << typeid(function_type).name() << std::endl;
    function_type f = wrapper_native_cast::template call<index-1, T, F>();

    typedef detail::create_primitive_type_descriptor
      <typename boost::mpl::begin<signature_parameter_types>::type
       , typename boost::mpl::end<signature_parameter_types>::type> create_descriptor;
    typedef boost::mpl::single_view<result_type> result_type_sequence;
    typedef detail::create_primitive_type_descriptor
      <typename boost::mpl::begin<result_type_sequence>::type
       , typename boost::mpl::end<result_type_sequence>::type> result_type_descriptor;
  
    typedef detail::split_descriptors<result_type_descriptor> split_descriptors_type;
    typename split_descriptors_type::template my_result<S>::type
      sequences = split_descriptors_type::split(entry.s);

    std::size_t parameters_length = create_descriptor::length
      (boost::fusion::begin(sequences.second), boost::fusion::end(sequences.second));
    signatures_buffer.resize(signatures_buffer.size()+1);
    signatures_buffer.back().resize
      (parameters_length + result_type_descriptor::length
        (boost::fusion::begin(sequences.first), boost::fusion::end(sequences.first))
        +3);
    std::vector<char>& signature = signatures_buffer.back();
    signature[0] = '(';
    signature[parameters_length+1] = ')';
    signature[signature.size()-1] = 0;
    create_descriptor::run(&signature[1], boost::fusion::begin(sequences.second)
                           , boost::fusion::end(sequences.second));
    result_type_descriptor::run(&signature[parameters_length+2]
                                , boost::fusion::begin(sequences.first)
                                , boost::fusion::end(sequences.first));
    assert(signature[signature.size()-1] == 0);
    std::cout << "signature for register: " << &signature[0] << std::endl;
    
    methods[index].name = const_cast<char*>(entry.name);
    methods[index].signature = &signature[0];
    methods[index].fnPtr = detail::function_safe_cast(f);
    return boost::mpl::size_t<index+1>();
  }

  JNINativeMethod* methods;
  std::list<std::vector<char> >& signatures_buffer;
};

}

template <typename T, typename S, typename C>
void register_class(reg::class_<T, S, C, false> cls)
{
  BOOST_MPL_ASSERT((boost::mpl::not_<boost::is_convertible<T, reg::tag::extends_tag> >));

  typedef typename boost::fusion::result_of::size<S>::type size_type;
  typedef typename boost::fusion::result_of::as_vector<S>::type sequence_type;

  // We need this to instantiate native_init_handler
  typedef void(*native_init_type)(JNIEnv*, jobject, jlong);
  native_init_type init = &javabind::detail::native_init_handler
    <T, sequence_type, C>;

  JNINativeMethod methods[size_type::value+1];
  methods[0].name = const_cast<char*>("nativeInit");
  methods[0].signature = const_cast<char*>("(J)V");
  methods[0].fnPtr = detail::function_safe_cast(init);

  std::list<std::vector<char> > signatures_buffer;
  boost::fusion::fold(cls.s, boost::mpl::size_t<1>()
                      , detail::initialize_native_method<T>
                      (methods, signatures_buffer));

  javabind::static_field<long_> bootstrap
    = cls.cls.template find_static_field<long_>("bootstrap");
  javabind::field<long_> peer = cls.cls.template find_field<long_>("peer");
  std::unique_ptr<detail::bootstrap_info_derived<sequence_type, C> >
    info(new detail::bootstrap_info_derived<sequence_type, C>
         (boost::fusion::as_vector(cls.s), peer, cls.c));

  bootstrap.set(cls.cls
                , reinterpret_cast<jlong>
                (static_cast<void*>
                 (static_cast<detail::bootstrap_info*>
                 (info.get()))));
  if(cls.cls.environment()
     ->RegisterNatives(cls.cls.raw(), methods, size_type::value+1) < 0)
  {
    throw std::runtime_error("Error registering native function");
  }
  info.release();
}

template <typename T, typename S, typename C>
void register_class(reg::class_<T, S, C, true> cls)
{
  BOOST_MPL_ASSERT((boost::is_convertible<T, reg::tag::extends_tag>));

  typedef typename boost::fusion::result_of::size<S>::type size_type;
  typedef typename boost::fusion::result_of::as_vector<S>::type sequence_type;

  // We need this to instantiate native_init_handler
  typedef void(*native_init_type)(JNIEnv*, jobject, jlong);
  native_init_type init = &javabind::detail::native_init_handler_with_extends
    <T, sequence_type, C>;

  JNINativeMethod methods[size_type::value+1];
  methods[0].name = const_cast<char*>("nativeInit");
  methods[0].signature = const_cast<char*>("(J)V");
  methods[0].fnPtr = detail::function_safe_cast(init);

  std::list<std::vector<char> > signatures_buffer;
  boost::fusion::fold(cls.s, boost::mpl::size_t<1>()
                      , detail::initialize_native_method<T>
                      (methods, signatures_buffer));

  javabind::static_field<long_> bootstrap
    = cls.cls.template find_static_field<long_>("bootstrap");
  javabind::field<long_> peer = cls.cls.template find_field<long_>("peer");
  javabind::field<long_> extends_peer = cls.get_base()
    .template find_field<long_>("peer");
  std::unique_ptr<detail::bootstrap_info_derived_with_extends<sequence_type, C> >
    info(new detail::bootstrap_info_derived_with_extends<sequence_type, C>
         (boost::fusion::as_vector(cls.s), peer, cls.c, extends_peer));

  bootstrap.set(cls.cls
                , reinterpret_cast<jlong>
                (static_cast<void*>
                 (static_cast<detail::bootstrap_info*>
                 (info.get()))));
  if(cls.cls.environment()
     ->RegisterNatives(cls.cls.raw(), methods, size_type::value+1) < 0)
  {
    throw std::runtime_error("Error registering native function");
  }
  info.release();
}

}

#endif
