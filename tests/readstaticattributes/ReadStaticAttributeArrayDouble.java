// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

package jvb.tests;

public class ReadStaticAttributeArrayDouble
{
    static final double[] attribute = new double[2];
    static
    {
        attribute[0] = 15.0;
        attribute[1] = 16.0;
    }
}
