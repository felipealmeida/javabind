// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CLASS_FILE_GENERATE_CLASS_FILE_HPP
#define JVB_CLASS_FILE_GENERATE_CLASS_FILE_HPP

#include <jni.h>

namespace jvb { namespace class_files {

template <typename OutputIterator>
void generate_class_file(class_ const& cls, OutputIterator iterator)
{
  static const unsigned int acc_public    = 0x0001;
  static const unsigned int acc_final     = 0x0010;
  static const unsigned int acc_super     = 0x0020;
  static const unsigned int acc_interface = 0x0200;
  static const unsigned int acc_abstract  = 0x0400;

  static const unsigned int constant_class_info = 7;
  static const unsigned int constant_utf8_info = 1;

  // magic number
  *iterator++ = 0xCA;
  *iterator++ = 0xFE;
  *iterator++ = 0xBA;
  *iterator++ = 0xBE;

  // major and minor versions
  *iterator++ = 0x00;
  *iterator++ = 0x00;
  *iterator++ = 0x00;
  *iterator++ = 0x33;

  // constant_pool_count
  *iterator++ = 0x00;
  *iterator++ = 0x05;

  // constant_pool has four elements
  *iterator++ = constant_class_info;
  *iterator++ = 0x00; // constant_index 2
  *iterator++ = 0x02; // 

  *iterator++ = constant_utf8_info;
  *iterator++ = 0x00;
  *iterator++ = 10;
  *iterator++ = 'H';
  *iterator++ = 'e';
  *iterator++ = 'l';
  *iterator++ = 'l';
  *iterator++ = 'o';
  *iterator++ = 'W';
  *iterator++ = 'o';
  *iterator++ = 'r';
  *iterator++ = 'l';
  *iterator++ = 'd';

  *iterator++ = constant_class_info;
  *iterator++ = 0x00; // constant_index 2
  *iterator++ = 0x04; // 

  *iterator++ = constant_utf8_info;
  *iterator++ = 0x00;
  *iterator++ = 16;
  *iterator++ = 'j';
  *iterator++ = 'a';
  *iterator++ = 'v';
  *iterator++ = 'a';
  *iterator++ = '/';
  *iterator++ = 'l';
  *iterator++ = 'a';
  *iterator++ = 'n';
  *iterator++ = 'g';
  *iterator++ = '/';
  *iterator++ = 'O';
  *iterator++ = 'b';
  *iterator++ = 'j';
  *iterator++ = 'e';
  *iterator++ = 'c';
  *iterator++ = 't';

  // access_flags
  *iterator++ = 0x00;
  *iterator++ = acc_public | acc_super;

  // thisclass
  *iterator++ = 0x00;
  *iterator++ = 0x01; // constant_index 1

  // superclass
  *iterator++ = 0x00;
  *iterator++ = 0x03;

  // interfaces_count
  *iterator++ = 0x00;
  *iterator++ = 0x00;

  // interfaces is empty

  // field_count
  *iterator++ = 0x00;
  *iterator++ = 0x00;

  // fields is empty

  // methods_count
  *iterator++ = 0x00;
  *iterator++ = 0x00;

  // methods is empty

  // attributes_count
  *iterator++ = 0x00;
  *iterator++ = 0x00;

  // attributes is empty
}

} }

#endif
