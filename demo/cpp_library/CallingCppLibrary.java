

public class CallingCppLibrary
{
    private native void print();
    public static void main(String[] args)
    {
        System.out.println("Hello World from Java");
        CallingCppLibrary self = new CallingCppLibrary();
        self.print();
    }

    static
    {
        System.out.println("Hello World from static clinit in Java");
        System.loadLibrary("cpp_library_demo");
    }
}
