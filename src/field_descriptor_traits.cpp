// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <javabind/field_descriptor_traits.hpp>
#include <javabind/primitives.hpp>

namespace javabind {

const char* field_descriptor_traits<string>::value  = "java/lang/String";
const char* field_descriptor_traits<char_>::value  = "C";
const char* field_descriptor_traits<int_>::value  = "I";
const char* field_descriptor_traits<double_>::value  = "D";
const char* field_descriptor_traits<void>::value  = "V";
const char* field_descriptor_traits<long_>::value  = "J";
const char* field_descriptor_traits<bool>::value  = "Z";
const char* field_descriptor_traits<byte>::value  = "B";
  //const char* field_descriptor_traits<array<char_> >::value  = "[I";

}
