// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_FILL_CLASS_FILE_CONTEXT_HPP
#define JVB_BINDING_FILL_CLASS_FILE_CONTEXT_HPP

#include <jvb/binding/placeholder/method.hpp>
#include <jvb/class_file/class_file.hpp>

#include <boost/proto/proto.hpp>
#include <boost/proto/traits.hpp>

namespace jvb { namespace binding {

struct fill_class_file_context
{
  fill_class_file_context(class_files::class_& cf)
    : cf(&cf) {}

  template <typename Expr
            , typename Tag = typename boost::proto::tag_of<Expr>::type
            , typename Value = typename boost::proto::result_of::value<Expr>::type
            >
  struct eval;

  template <typename Expr, typename Sig, typename F>
  struct eval<Expr, boost::proto::tag::terminal
              , binding::placeholder::method_value<Sig, F> >
  {
    typedef void result_type;
    void operator()(Expr const& expr, fill_class_file_context& ctx) const
    {
    }
  };

  class_files::class_* cf;
};

} }

#endif
