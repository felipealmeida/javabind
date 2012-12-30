// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

package jvb.tests;

public class CallMethodArrayByte
{
    public CallMethodArrayByte() {}

    public byte[] method()
    {
        byte[] v = new byte[2];
        v[0] = 15;
        v[1] = 16;
        return v;
    }
}
