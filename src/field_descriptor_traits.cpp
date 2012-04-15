// (c) Copyright 2012 Felipe Magno de Almeida
//
// All rights reserved

#include <javabind/field_descriptor_traits.hpp>

namespace javabind {

const char* field_descriptor_traits<string>::value  = "java/lang/String";
const char* field_descriptor_traits<jint>::value  = "I";
const char* field_descriptor_traits<jdouble>::value  = "D";
const char* field_descriptor_traits<void>::value  = "V";
const char* field_descriptor_traits<jlong>::value  = "J";
const char* field_descriptor_traits<jboolean>::value  = "Z";

}
