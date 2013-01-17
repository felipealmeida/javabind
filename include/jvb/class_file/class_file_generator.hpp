// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef JVB_CLASS_FILE_CLASS_FILE_GENERATOR_HPP
#define JVB_CLASS_FILE_CLASS_FILE_GENERATOR_HPP

#include <jvb/class_file/class_.hpp>

#include <boost/spirit/home/karma.hpp>
#include <boost/phoenix.hpp>
#include <boost/integer.hpp>

#include <iostream>

namespace jvb { namespace class_files {

namespace karma = boost::spirit::karma;
namespace spirit = boost::spirit;

template <typename OutputIterator>
struct fields_generator
  : karma::grammar<OutputIterator
                   , karma::locals<unsigned int>
                   , std::vector<class_files::name_descriptor_pair>
                   (unsigned int, unsigned int)>
{
  fields_generator() : fields_generator::base_type(start)
  {
    using karma::_1;
    using karma::_r1;
    using karma::_r2;
    using karma::_a;
    using karma::_val;
    using karma::big_word;
    using karma::eps;
    using karma::repeat;
    namespace phoenix = boost::phoenix;
    using phoenix::val;
    start = 
      repeat(phoenix::size(_val))
      [
       big_word[_1 = _r2]                        // u2 access_flags
       << big_word[_1 = _a*2 + _r1]              // u2 name_index
       << big_word[_1 = _a*2 + _r1 + 1]          // u2 descriptor_index
       << big_word[_1 = 0]                       // u2 attributes_count
       << eps[++_a]
      ]
      ;
  }

  karma::rule<OutputIterator
              , karma::locals<unsigned int>
              , std::vector<class_files::name_descriptor_pair>
              (unsigned int, unsigned int)> start;
};

template <typename OutputIterator>
struct not_implemented_method_generator
  : karma::grammar<OutputIterator
                   , std::vector<class_files::name_descriptor_pair>
                   (unsigned int)
                   , karma::locals<unsigned int> >
{
  not_implemented_method_generator()
    : not_implemented_method_generator::base_type(start)
  {
    using karma::_1;
    using karma::_a;
    using karma::_r1;
    using karma::_val;
    using karma::big_word;
    using karma::byte_;
    using karma::eps;
    using karma::repeat;
    namespace phoenix = boost::phoenix;
    using phoenix::val;
    start = 
      big_word[_1 = phoenix::size(_val)]
      << repeat(phoenix::size(_val))
      [
       byte_(1)
       << byte_(1)
       << big_word(_a * 2 + _r1)
       << big_word(_a * 2 + _r1 + 1)
       << big_word(0)
       << eps[++_a]
      ]
      ;
  }

  karma::rule<OutputIterator
              , std::vector<class_files::name_descriptor_pair>
              (unsigned int)
              , karma::locals<unsigned int> > start;
};

template <typename OutputIterator>
struct class_file_generator
  : karma::grammar<OutputIterator
                   , karma::locals<unsigned int, unsigned int, unsigned int>
                   , class_files::class_
                   (unsigned int)>
{
  class_file_generator() : class_file_generator::base_type(start)
  {
    using karma::_1;
    using karma::_a; using karma::_b; using karma::_c;
    using karma::_val;
    using karma::_r1;
    using karma::big_word;
    using karma::big_dword;
    using karma::eps;
    using boost::spirit::byte_;
    using boost::phoenix::size;
    using boost::phoenix::at_c;
    static const unsigned int constant_class_info = 7;
    static const unsigned int constant_utf8_info = 1;
    // static const unsigned int acc_public    = 0x0001;
    // // static const unsigned int acc_final     = 0x0010;
    // static const unsigned int acc_super     = 0x0020;
    // // static const unsigned int acc_interface = 0x0200;
    // // static const unsigned int acc_abstract  = 0x0400;
    static const unsigned int static_fields_index = 0;
    static const unsigned int fields_index = 1;
    static const unsigned int not_implemented_method_index = 2;
    static const unsigned int name_index = 4;
    static const unsigned int extends_name_index = 5;
    // _a = offset of constants for not implemented methods
    // _b = offset of constants for static fields
    // _c = offset of constants for fields
    start =
         big_dword(0xCAFEBABEU)
      << karma::eps(size(at_c<not_implemented_method_index>(_val)) >= 1u)
      << big_word(0x00U)
      << big_word(0x2EU)
      << (             // constant pool
          big_word
          [
           _1 =   2*size(at_c<not_implemented_method_index>(_val))
                + 2*size(at_c<static_fields_index>(_val))
                + 2*size(at_c<fields_index>(_val))
                + 5
           ]
          << class_info_constant[_1 = 2]
          << utf8_info_constant[_1 = at_c<name_index>(_val)]
          << class_info_constant[_1 = 4]
          << utf8_info_constant[_1 = at_c<extends_name_index>(_val)]
          << eps[ _c = _b = _a = 5 ]
          << (*name_descriptor)[_1 = at_c<not_implemented_method_index>(_val)]
          << eps[ _c = (_b += size(at_c<not_implemented_method_index>(_val))*2) ]
          << (*name_descriptor)[_1 = at_c<static_fields_index>(_val)]
          << eps[ _c += size(at_c<static_fields_index>(_val))*2 ]
          << (*name_descriptor)[_1 = at_c<fields_index>(_val)]
         )
      << big_word(_r1) // access flags
      << big_word(1)   // constant index for class_info_constant 1
      << big_word(3)   // constant index for class_info_constant 3
      << big_word(0)   // 0 interfaces
      << big_word[_1 = size(at_c<static_fields_index>(_val))
                       + size(at_c<fields_index>(_val))
                 ]
      << fields(_b, 2 + 8)[_1 = at_c<static_fields_index>(_val)]
      << fields(_c, 2 /*+ 8*/)[_1 = at_c<fields_index>(_val)]
      << not_implemented_method(_a)[_1 = at_c<not_implemented_method_index>(_val)]
      << big_word(0)   // attributes_count 0 
      ;

    name_descriptor %=
      utf8_info_constant
      << utf8_info_constant
      ;

    utf8_info_constant = 
      byte_(constant_utf8_info)
      << big_word[_1 = size(_val)]
      << karma::string[_1 = _val]
      ;

    class_info_constant %= 
      byte_(constant_class_info)
      << big_word // constant_index
      ;
  }

  fields_generator<OutputIterator> fields;
  karma::rule<OutputIterator, boost::uint_t<16u>::least()> class_info_constant;
  karma::rule<OutputIterator, std::string()> utf8_info_constant;
  karma::rule<OutputIterator, class_files::name_descriptor_pair()> name_descriptor;
  not_implemented_method_generator<OutputIterator> not_implemented_method;
  karma::rule<OutputIterator
              , karma::locals<unsigned int, unsigned int, unsigned int>
              , class_files::class_(unsigned int)> start;
};

} }

#endif
