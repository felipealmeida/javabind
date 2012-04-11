// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#include <javabind/class.hpp>

#include <javabind/object.hpp>

namespace javabind {

javabind::class_ object::class_() const
{
  return javabind::class_(env->GetObjectClass(o), env);
}


}

