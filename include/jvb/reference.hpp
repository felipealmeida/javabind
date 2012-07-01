// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_REFERENCE_HPP
#define JVB_REFERENCE_HPP

namespace jvb {

template <typename T>
struct ref
{
  ref()
  {
  }
  ref(environment e)
    : obj(e)
  {
  }

  T const* operator->() const
  {
    return &obj;
  }

private:
  T obj;
};

template <typename T>
struct cleanup_ref
{
  
};

template <typename T>
struct global_ref
{
  
};

}

#endif
