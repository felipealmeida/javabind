// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING) || !BOOST_PP_IS_ITERATING

#ifndef JVB_BINDING_CONSTRUCTOR_FUNCTION_HPP
#define JVB_BINDING_CONSTRUCTOR_FUNCTION_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/binding/peer_info.hpp>
#include <jvb/binding/fields_names.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/enum_params.hpp>

namespace jvb { namespace binding {

template <typename T, typename Allocator, typename Result, std::size_t I, std::size_t N>
struct constructor_function
{
  typedef void result_type;
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, JVB_MAX_ARGS, "jvb/binding/constructor_function.hpp"))
#include BOOST_PP_ITERATE()
};

} }

#endif
#else

#if BOOST_PP_ITERATION() != 0
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
#endif
void operator()(jvb::environment e, jvb::Object obj
                BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
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
  boost::function<Result(jvb::environment BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), A))>*
    f = static_cast<boost::function<Result(jvb::environment
                                           BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), A))>*>(fp);

  std::auto_ptr<binding::peer_info<T, N> >
    peer_info(new binding::peer_info<T, N>
              (*vtable, (*f)(e BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a)) ));

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

#endif
