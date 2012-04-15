// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#ifndef JAVABIND_REG_CLASS_HPP
#define JAVABIND_REG_CLASS_HPP

#include <javabind/class.hpp>
#include <javabind/reg/function_entry.hpp>
#include <javabind/reg/constructor.hpp>

#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/mpl/bool.hpp>

namespace javabind { namespace reg {

template <typename T, typename S = boost::fusion::vector0<>
          , typename Constructor = default_constructor_tag
          , bool has_base = false>
struct class_;

namespace detail {

template <typename T, typename S, typename Constructor, bool has_base>
struct class_traits
{
  typedef T object_type;
  typedef S sequence_type;
  typedef Constructor constructor_type;
  typedef boost::mpl::bool_<has_base> has_base_type;
  typedef class_<T, S, Constructor, has_base> derived_type;
};

}

template <typename Derived>
struct class_impl;

template <typename T, typename S, typename Constructor>
struct class_<T, S, Constructor, false>
  : class_impl<detail::class_traits<T, S, Constructor, false> >
{
  typedef class_impl<detail::class_traits<T, S, Constructor, false> > impl_type;

  class_(javabind::class_ cls, javabind::class_ base = javabind::class_()
         , S s = boost::fusion::vector0<>()
         , Constructor c = Constructor())
    : impl_type(cls, s, c)
  {}

  class_<T, S, Constructor, true> base(javabind::class_ b) const
  {
    return class_<T, S, Constructor, true>(this->cls, b, this->s, this->c);
  }

  javabind::class_ get_base() const { return javabind::class_(); }
};

template <typename T, typename S, typename Constructor>
struct class_<T, S, Constructor, true>
  : class_impl<detail::class_traits<T, S, Constructor, true> >
{
  typedef class_impl<detail::class_traits<T, S, Constructor, true> > impl_type;

  class_(javabind::class_ cls, javabind::class_ base
         ,  S s = boost::fusion::vector0<>()
         , Constructor c = Constructor())
    : impl_type(cls, s, c), base_(base)
  {}

  javabind::class_ get_base() const { return base_; }

  javabind::class_ base_;
};

template <typename Traits>
struct class_impl
{
  typedef typename Traits::object_type object_type;
  typedef typename Traits::sequence_type sequence_type;
  typedef typename Traits::constructor_type constructor_type;
  typedef typename Traits::has_base_type has_base_type;
  typedef typename Traits::derived_type derived_type;

  class_impl(javabind::class_ cls, sequence_type s, constructor_type c)
    : cls(cls), s(s), c(c)
  {}

  derived_type const& derived() const
  { return static_cast<derived_type const&>(*this); }

  template <typename F>
  reg::class_<object_type, typename boost::fusion::result_of::push_back
              <sequence_type const, function_entry<F, F> >::type, constructor_type
              , has_base_type::type::value>
  def(const char* name, F f) const
  {
    typedef typename boost::fusion::result_of::push_back<sequence_type const
                                                         , function_entry<F, F> >::type
      new_sequence;
    typedef reg::class_<object_type, new_sequence, constructor_type
                        , has_base_type::type::value> new_class;

    return new_class
      (cls, derived().get_base()
       , boost::fusion::push_back(s, function_entry<F, F>(name, f)), c);
  }

  template <typename Sig, typename F>
  reg::class_<object_type, typename boost::fusion::result_of::push_back
              <sequence_type const, function_entry<Sig, F> >::type, constructor_type
              , has_base_type::type::value>
  def(const char* name, F f) const
  {
    typedef typename boost::fusion::result_of::push_back<sequence_type const
                                                         , function_entry<Sig, F> >::type
      new_sequence;
    typedef reg::class_<object_type, new_sequence, constructor_type
                        , has_base_type::type::value> new_class;

    return new_class
      (cls, derived().get_base()
       , boost::fusion::push_back(s, function_entry<Sig, F>(name, f)), c);
  }

  template <typename F>
  reg::class_<object_type, sequence_type, F> constructor(F f) const
  {
    BOOST_MPL_ASSERT((boost::is_same<constructor_type, default_constructor_tag>));
    return reg::class_<object_type, sequence_type, F>(cls, derived().get_base(), s, f);
  }

  template <typename T1>
  static T1 const as_const(T1 v) { return v; }

  javabind::class_ cls;
  sequence_type s;
  constructor_type c;
};

} }

#endif
