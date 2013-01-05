// (c) Copyright 2012 Felipe Magno de Almeida
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

package jvb.tests;

public class Implements implements Interface1, Interface2
{
    public boolean bar_called = false;
    public boolean foo_called = false;

    public Implements()
    {
    }

    public void bar()
    {
        bar_called = true;
    }

    public void foo()
    {
        foo_called = true;
    }
}

