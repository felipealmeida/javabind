// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

package jvb.tests;

public class ReadStaticAttributeArrayChar
{
    static final char[] attribute = new char[2];
    static
    {
        attribute[0] = 'a';
        attribute[1] = 'b';
    }
}
