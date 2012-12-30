// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

package jvb.tests;

public class CallMethodArrayObject
{
    public CallMethodArrayObject() {}

    public CallMethodVoid[] method()
    {
        CallMethodVoid[] v = new CallMethodVoid[2];
        v[0] = new CallMethodVoid();
        v[1] = null;
        return v;
    }
}
