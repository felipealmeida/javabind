// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#include <javabind/field_descriptor_traits.hpp>

namespace javabind {

const char* field_descriptor_traits<std::string>::value  = "java/lang/String";
const char* field_descriptor_traits<jint>::value  = "I";

}
