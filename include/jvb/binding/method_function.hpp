// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING) || !BOOST_PP_IS_ITERATING

#ifndef JVB_BINDING_METHOD_FUNCTION_HPP
#define JVB_BINDING_METHOD_FUNCTION_HPP

#include <jvb/detail/max_args.hpp>
#include <jvb/binding/virtual_table.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>

namespace jvb { namespace binding {

template <int I, int N, typename R, typename PeerClass>
struct method_function
{
  typedef R result_type;
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, JVB_MAX_ARGS, "jvb/binding/method_function.hpp"))
#include BOOST_PP_ITERATE()
};

} }

#endif
#else

#if BOOST_PP_ITERATION() != 0
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
#endif
result_type operator()(jvb::environment e, jvb::Object obj
                       BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  std::cout << "method_function" << std::endl;
  {
    const char* d = "J";
    ::jclass c = obj.class_(e).raw();
    assert(c != 0);
    jfieldID fid = e.raw()->GetStaticFieldID
      (c, "javabind_vtable", d);
    assert(fid != 0);
    jlong rl = e.raw()->GetStaticLongField(c, fid);
    void* p = 0;
    std::memcpy(&p, &rl, sizeof(void*));
    binding::virtual_table<N>* virtual_table
      = static_cast<binding::virtual_table<N>*>(p);
    void* fp = virtual_table->methods[I].function_object.get();
    assert(fp != 0);
    boost::function<result_type(PeerClass&, jvb::environment)>*
      f = static_cast<boost::function<result_type(PeerClass&, jvb::environment)>*>(fp);
    PeerClass peer;
    (*f)(peer, e BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
  }
}

#endif
