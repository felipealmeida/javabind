// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_FIELD_HPP
#define JAVABIND_FIELD_HPP

#include <javabind/detail/tag.hpp>
#include <javabind/detail/get_static_field.hpp>
#include <javabind/detail/get_field.hpp>
#include <javabind/detail/set_static_field.hpp>
#include <javabind/detail/set_field.hpp>

namespace javabind {

struct class_;

template <typename T>
struct static_field
{
  static_field() : id(0) {}
  static_field( ::jfieldID id)
    : id(id)
  {}

  T get(class_ const& cls) const
  {
    return detail::get_static_field(cls.environment(), cls.raw(), id, detail::tag<T>());
  }
  void set(class_ const& cls, T v)
  {
    detail::set_static_field(cls.environment(), cls.raw(), id, v);
  }

  jfieldID raw() const { return id; }
private:
  jfieldID id;
};

template <typename T>
struct field
{
  field() : id(0) {}
  field( ::jfieldID id)
    : id(id)
  {}

  T get(object const& o) const
  {
    return detail::get_field(o.environment(), o.raw(), id, detail::tag<T>());
  }
  void set(object const& o, T v)
  {
    detail::set_field(o.environment(), o.raw(), id, v);
    assert(detail::get_field(o.environment(), o.raw(), id, detail::tag<T>()) == v);
  }

  jfieldID raw() const { return id; }
private:
  jfieldID id;
};

}

#endif
