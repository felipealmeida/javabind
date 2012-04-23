// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#include <javabind/field_descriptor_traits.hpp>
#include <javabind/primitives.hpp>

namespace javabind {

const char* field_descriptor_traits<string>::value  = "java/lang/String";
const char* field_descriptor_traits<char_>::value  = "C";
const char* field_descriptor_traits<int_>::value  = "I";
const char* field_descriptor_traits<double_>::value  = "D";
const char* field_descriptor_traits<void>::value  = "V";
const char* field_descriptor_traits<long_>::value  = "J";
const char* field_descriptor_traits<boolean>::value  = "Z";
const char* field_descriptor_traits<array<char_> >::value  = "[I";

}
