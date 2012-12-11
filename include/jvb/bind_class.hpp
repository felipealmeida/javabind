// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BIND_CLASS_HPP
#define JVB_BIND_CLASS_HPP

#include <jvb/jvb.hpp>
#include <jvb/bind_function.hpp>
#include <jvb/detail/create_signature.hpp>
#include <jvb/binding/definitions.hpp>
#include <jvb/binding/method_traits.hpp>
#include <jvb/binding/constructor_traits.hpp>
#include <jvb/binding/fields_names.hpp>
#include <jvb/binding/peer_info.hpp>
#include <jvb/binding/method_function.hpp>
#include <jvb/class_file/class_file_generator.hpp>
#include <jvb/class_file/class_.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/plus.hpp>

#include <boost/filesystem/path.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

#include <boost/bind.hpp>

#include <fstream>

namespace jvb {

namespace binding {

struct public_tag {};

public_tag public_ = {};

}

namespace mpl = boost::mpl;
namespace fusion = boost::fusion;

namespace binding {

template <typename T, typename Allocator, typename Result, std::size_t I, std::size_t N>
struct constructor
{
  typedef void result_type;
  result_type operator()(environment e, Object obj) const
  {
    assert(obj.raw() != 0);
    BOOST_MPL_ASSERT((boost::mpl::bool_<(sizeof(void*) <= sizeof(::jlong))>));
    // typename Allocator::template rebind<T>::other allocator;
    std::cout << "constructor wrapper" << std::endl;
    // void* p = allocator.allocate(1, 0);
    // T* object = new (p) T;

    binding::virtual_table<N>const* vtable;
    ::jclass c = obj.class_(e).raw();
    {
      const char* d = "J";
      assert(c != 0);
      jfieldID fid = e.raw()->GetStaticFieldID
        (c, javabind_vtable_field_name, d);
      assert(fid != 0);
      jlong rl = e.raw()->GetStaticLongField(c, fid);
      void* p = 0;
      std::memcpy(&p, &rl, sizeof(void*));
      vtable = static_cast<binding::virtual_table<N>*>(p);
    }
    void* fp = vtable->methods[I].function_object.get();
    assert(fp != 0);
    boost::function<Result(jvb::environment)>*
      f = static_cast<boost::function<Result(jvb::environment)>*>(fp);

    std::auto_ptr<binding::peer_info<T, N> >
      peer_info(new binding::peer_info<T, N>
                (*vtable, (*f)(e) ));

    {
      ::jlong rl = 0;
      void* p = peer_info.release();
      std::memcpy(&rl, &p, sizeof(void*));
      const char* d = "J";
      assert(c != 0);
      jfieldID fid = e.raw()->GetFieldID
        (c, binding::javabind_peer_info_field_name, d);
      assert(fid != 0);
      e.raw()->SetLongField(obj.raw(), fid, rl);
    }

  }
};

}

struct add_method
{
  typedef void result_type;
  
  template <typename FunDef, typename Modifiers, typename F>
  result_type operator()(class_files::class_& cls
                         , environment e
                         , binding::method_def<FunDef, Modifiers, F> const& method) const
  {
    class_files::name_descriptor_pair m;
    boost::fusion::at_c<0>(m) = FunDef::name();
    typedef typename FunDef::sig_type sig_type;
    typedef typename boost::function_types::result_type<sig_type>::type return_type;
    typedef typename boost::function_types::parameter_types<sig_type>::type parameter_types;
    detail::descriptors::descriptor_function<return_type, parameter_types>
      (e, std::back_inserter(boost::fusion::at_c<1>(m)));
    cls.not_implemented_methods.push_back(m);
  }
};

struct add_factory_constructor
{
  typedef void result_type;
  
  template <typename Sig, typename Modifiers, typename F>
  result_type operator()(class_files::class_& cls
                         , environment e
                         , binding::factory_constructor_def<Sig, Modifiers, F> const& constructor) const
  {
    std::cout << "add_factory_constructor" << std::endl;
    class_files::name_descriptor_pair native_method;
    boost::fusion::at_c<0>(native_method) = "<init>";
    typedef Sig sig_type;
    typedef typename boost::function_types::parameter_types<sig_type>::type parameter_types;
    detail::descriptors::descriptor_function<void, parameter_types>
      (e, std::back_inserter(boost::fusion::at_c<1>(native_method)));
    cls.not_implemented_methods.push_back(native_method);
  }
};

template <typename PeerClass, typename Allocator, std::size_t N>
struct bind_method_call
{
  bind_method_call(Class const& cls
                   , environment e
                   , binding::virtual_table<N>& vtable)
    : cls(cls), vtable(vtable), e(e) {}

  template <typename T> struct result;
  template <typename This, typename Def, std::size_t I>
  struct result<This(mpl::size_t<I>const&, Def&)>
  {
    typedef mpl::size_t<I+1> type;
  };

  template <typename FunDef, typename Modifiers, typename F, std::size_t I>
  mpl::size_t<I+1> operator()(mpl::size_t<I>
                              , binding::method_def<FunDef, Modifiers, F> const& method
                             ) const
  {
    typedef binding::method_traits<F, PeerClass> method_traits;
    typedef typename method_traits::result_type result_type;

    std::cout << "bind_method_call::method_def" << std::endl;
    jvb::bind_function<typename method_traits::binding_signature
                       , binding::method_function<I, N, result_type, PeerClass> >
      (e, cls, FunDef::name());

    typedef typename method_traits::template function_caller<F> function_caller_type;

    vtable.methods[I].function_object =
      boost::shared_ptr<void>
      (new boost::function<typename method_traits::caller_signature>
       (function_caller_type(method.f)));

    std::cout << "typeid(F) " << typeid(F).name() << std::endl;

    return mpl::size_t<I+1>();
  }

  template <typename Sig, typename Modifiers, typename F, std::size_t I>
  mpl::size_t<I+1> operator()(mpl::size_t<I>
                              , binding::factory_constructor_def<Sig, Modifiers, F> const& method
                             ) const
  {
    namespace function_types = boost::function_types;
    typedef typename function_types::parameter_types<Sig> sig_parameter_types;
    typedef typename function_types::function_type
      <typename mpl::push_front<sig_parameter_types, F>::type>::type result_of_argument;
    typedef typename boost::result_of<result_of_argument>::type result_type;
    typedef typename function_types::function_type
      <typename mpl::push_front<sig_parameter_types, result_type>::type>::type signature_type;

    typedef binding::constructor_traits<signature_type> constructor_traits;

    std::cout << "bind_method_call::factory_constructor_def" << std::endl;
    jvb::bind_function<void(jvb::environment, jvb::Object)
                       , binding::constructor<PeerClass, Allocator, result_type, I, N> >
      (e, cls, "<init>");

    typedef typename constructor_traits::template function_caller<F> function_caller_type;

    vtable.methods[I].function_object =
      boost::shared_ptr<void>
      (new boost::function<result_type(jvb::environment)>
       (function_caller_type(method.f)));

    return mpl::size_t<I+1>();
  }

  Class const& cls;
  binding::virtual_table<N>& vtable;
  environment e;
};

template <typename C, typename P, typename Generate, typename Allocator, typename Methods, typename FactoryConstructors>
Class bind_class_impl(environment e, Allocator allocator, Methods methods, FactoryConstructors factory_constructors)
{
  class_files::class_ cf(C::name(), C::base_type::name());

  cf.static_fields.push_back(class_files::name_descriptor_pair(binding::javabind_vtable_field_name, "J"));
  cf.fields.push_back(class_files::name_descriptor_pair(binding::javabind_peer_info_field_name, "J"));

  fusion::for_each(methods, boost::bind(add_method(), boost::ref(cf), e, _1));
  // assert(cf.not_implemented_methods.size() == fusion::size(methods));
  fusion::for_each(factory_constructors, boost::bind(add_factory_constructor(), boost::ref(cf), e, _1));
  // assert(cf.not_implemented_methods.size() == fusion::size(methods) + fusion::size(factory_constructors));
  // assert(fusion::size(factory_constructors) >= 1);

  std::vector<char> class_file;
  if(Generate::value)
  {
    class_files::class_file_generator<std::back_insert_iterator<std::vector<char> > >
      class_file_generator;
    namespace karma = boost::spirit::karma;
    if(!karma::generate(std::back_inserter(class_file)
                        , class_file_generator(0x21)[karma::_1 = cf]))
    {
      throw std::runtime_error("Failed generating class file");
    }
    {
      boost::filesystem::path filename (C::name());
      filename.replace_extension(".class");
      filename = filename.filename();
      std::cout << "Writing to Filename " << filename.string() << std::endl;
      std::ofstream file(filename.string().c_str());
      std::copy(class_file.begin(), class_file.end(), std::ostream_iterator<char>(file));
    }
  }
  else
  {
    boost::filesystem::path filename (C::name());
    filename.replace_extension(".class");
    filename = filename.filename();
    std::cout << "Reading from Filename " << filename.string() << std::endl;
    std::ifstream file(filename.string().c_str());
    file.seekg(0, std::ios::end);
    std::size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    class_file.resize(size);
    assert(size != 0);
    file.rdbuf()->sgetn(&class_file[0], size);
  }

  std::cout << "Calling DefineClass for buffer of size " << class_file.size() << std::endl;

  if(jclass cls_raw = e.raw()->DefineClass(C::name(), 0, reinterpret_cast<const jbyte*>(&class_file[0])
                                       , class_file.size()))
  {
    std::cout << "Success loading class" << std::endl;

    jvb::Class cls(cls_raw);

    typedef typename mpl::size<Methods>::type methods_size;
    typedef typename mpl::size<Methods>::type factory_constructors_size;
    typedef typename mpl::plus<methods_size, factory_constructors_size>::type
      virtual_table_size;

    typedef binding::virtual_table<virtual_table_size::value> virtual_table_type;
    std::auto_ptr<virtual_table_type>
      vtable(new virtual_table_type);

    bind_method_call<P, Allocator, virtual_table_size::value> binder(cls, e, *vtable);

    fusion::fold(methods, mpl::size_t<0>(), binder);
    fusion::fold(factory_constructors, mpl::size_t<methods_size::value>(), binder);

    {
      ::jlong rl = 0;
      void* p = vtable.release();
      std::memcpy(&rl, &p, sizeof(void*));
      const char* d = "J";
      ::jclass c = cls.raw();
      assert(c != 0);
      jfieldID fid = e.raw()->GetStaticFieldID
        (c, binding::javabind_vtable_field_name, d);
      assert(fid != 0);
      e.raw()->SetStaticLongField(c, fid, rl);
    }

    std::cout << "Success binding the method" << std::endl;

    return cls;
  }
  else
  {
    std::cout << "Failed defining class" << std::endl;
    e.raw()->ExceptionDescribe();
    throw std::runtime_error("Couldn't define class");
  }
}

template <typename V, typename Finder, typename D>
struct get_param
{
  typedef typename mpl::find_if
  <V, typename mpl::lambda<Finder>::type
  >::type iterator_type;
  typedef typename mpl::distance
  <typename mpl::begin<V>::type, iterator_type>::type
  index_type;
  typedef typename mpl::distance
  <typename mpl::begin<V>::type, typename mpl::end<V>::type>::type
  max_index_type;

  template <typename P, typename T>
  static typename fusion::result_of::at_c<P, index_type::value>::type
  call_impl(P& params, T)
  {
    return fusion::at_c<index_type::value>(params);
  }

  template <typename P>
  static D call_impl(P& params, max_index_type)
  {
    return D();
  }

  template <typename P>
  static
  typename mpl::if_
  <mpl::equal_to<index_type, max_index_type>
   , D
   , typename boost::remove_reference
   <typename fusion::result_of::at_c<P, index_type::value>::type>::type
  >::type
  call(P& params)
  {
    return call_impl(params, index_type());
  }
};

template <typename T> struct is_allocator : mpl::false_ {};
template <typename T> struct is_allocator<binding::allocator_def<T> > : mpl::true_ {};

template <typename T, typename F, typename E = void>
struct is_seq_of_apply : mpl::false_ {};

template <typename T, typename F>
struct is_seq_of_apply<T, F
                       , typename boost::enable_if
                       <typename mpl::eval_if
                        <boost::is_same<mpl::void_, T>
                         , mpl::false_
                         , mpl::greater<mpl::size<T>, mpl::int_<0> >
                        >::type
                        >::type
                       >
 : mpl::apply1<F, typename boost::remove_reference<typename mpl::at_c<T, 0u>::type>::type>
{};

template <typename F>
struct is_seq_of
{
  template <typename T> struct apply : is_seq_of_apply<T, F> {};
};

template <typename T> struct is_method_def : mpl::false_ {};
template <typename A0, typename A1, typename A2>
struct is_method_def<binding::method_def<A0, A1, A2> > : mpl::true_ {};

template <typename T>
struct is_factory_constructor_def : mpl::false_ {};
template <typename A0, typename A1, typename A2>
struct is_factory_constructor_def<binding::factory_constructor_def<A0, A1, A2> > : mpl::true_ {};

template <typename C, typename P, typename A0, typename A1, typename A2>
Class bind_class(environment e, A0 a0, A1 a1, A2 a2)
{
  fusion::vector3<A0&, A1&, A2&> params(a0, a1, a2);
  typedef mpl::vector3<A0, A1, A2> param_types;
  typedef jvb::get_param<param_types, is_allocator<mpl::_>
                         , std::allocator<void> > get_allocator;

  typedef is_seq_of
    <typename mpl::lambda<jvb::is_method_def<mpl::_1> >::type>
    is_method_def;
  typedef is_seq_of
    <typename mpl::lambda<jvb::is_factory_constructor_def<mpl::_1> >::type>
    is_factory_constructor_def;

  typedef jvb::get_param<param_types, is_method_def
                         , fusion::vector0<> > get_methods;
  typedef jvb::get_param<param_types, is_factory_constructor_def
                         , fusion::vector0<> > get_factory_constructors;
  return bind_class_impl<C, P, mpl::true_>(e, get_allocator::call(params)
                               , get_methods::call(params)
                               , get_factory_constructors::call(params));
}

}

#endif
