// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

package jvb.tests;

public class ReadStaticAttributeArrayBoolean
{
    static final boolean[] attribute = new boolean[2];
    ReadStaticAttributeArrayBoolean()
    {
        attribute[0] = true;
        attribute[1] = false;
    }
}
