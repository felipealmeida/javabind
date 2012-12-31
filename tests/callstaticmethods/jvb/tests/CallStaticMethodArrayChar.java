// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

package jvb.tests;

public class CallStaticMethodArrayChar
{
    static public char[] method()
    {
        char[] v = new char[2];
        v[0] = 'a';
        v[1] = 'b';
        return v;
    }
}
