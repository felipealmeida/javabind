// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_BINDING_DEFINITIONS_HPP
#define JVB_BINDING_DEFINITIONS_HPP

namespace jvb { namespace binding {

template <typename FunctionDefinition, typename ModifierExpr, typename F>
struct method_def
{
  method_def(F f) : f(f) {}

  F f;
};

template <typename FunctionDefinition, typename ModifierExpr, typename F>
method_def<FunctionDefinition, ModifierExpr, F> method(ModifierExpr modifier_expr, F f)
{
  return method_def<FunctionDefinition, ModifierExpr, F>(f);
}

template <typename Signature, typename ModifierExpr, typename F>
struct factory_constructor_def
{
  factory_constructor_def(F f) : f(f) {}

  F f;
};

template <typename Signature, typename ModifierExpr, typename F>
factory_constructor_def<Signature, ModifierExpr, F> factory_constructor(ModifierExpr modifier_expr, F f)
{
  return factory_constructor_def<Signature, ModifierExpr, F>(f);
}

template <typename Allocator>
struct allocator_def
{
  allocator_def(Allocator allocator) : allocator(allocator) {}
  Allocator allocator;
};

template <typename Allocator>
allocator_def<Allocator> allocator(Allocator allocator)
{
  return allocator_def<Allocator>(allocator);
}

} }

#endif
