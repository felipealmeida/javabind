// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_FIELD_HPP
#define JVB_FIELD_HPP

#include <jvb/environment.hpp>
#include <jvb/detail/get_field.hpp>
#include <jvb/detail/set_field.hpp>
#include <jvb/detail/get_static_field.hpp>
#include <jvb/detail/set_static_field.hpp>

#include <iostream>

namespace jvb {

template <typename T>
struct field
{
};

template <typename C, typename T>
T read_field(environment e, jobject obj, const char* name)
{
  std::string descriptor;
  jvb::detail::descriptors::descriptor<T>
    (e, std::back_inserter(descriptor));
  jclass cls = e.raw()->GetObjectClass(obj);
  jfieldID fid = e.raw()->GetFieldID(cls, name, descriptor.c_str());
  assert(fid != 0);
  return jvb::detail::get_field(e.raw(), obj, fid, jvb::detail::tag<T>());
}

template <typename C, typename T>
void write_field(environment e, jobject obj, const char* name, T value)
{
  std::string descriptor;
  jvb::detail::descriptors::descriptor<T>
    (e, std::back_inserter(descriptor));
  jclass cls = e.raw()->GetObjectClass(obj);
  jfieldID fid = e.raw()->GetFieldID(cls, name, descriptor.c_str());
  assert(fid != 0);
  jvb::detail::set_field(e.raw(), obj, fid, value);
}

template <typename C, typename T>
T read_static_field(environment e, jvb::class_ class_, const char* name)
{
  std::string descriptor;
  jvb::detail::descriptors::descriptor<T>
    (e, std::back_inserter(descriptor));
  jclass cls = class_.raw();
  jfieldID fid = e.raw()->GetStaticFieldID(cls, name, descriptor.c_str());
  assert(fid != 0);
  return jvb::detail::get_static_field(e.raw(), cls, fid, jvb::detail::tag<T>());
}

template <typename C, typename T>
void write_static_field(environment e, jvb::class_ class_, const char* name, T value)
{
  std::string descriptor;
  jvb::detail::descriptors::descriptor<T>
    (e, std::back_inserter(descriptor));
  jclass cls = class_.raw();
  jfieldID fid = e.raw()->GetStaticFieldID(cls, name, descriptor.c_str());
  assert(fid != 0);
  jvb::detail::set_static_field(e.raw(), cls, fid, value);
}

}

#endif
