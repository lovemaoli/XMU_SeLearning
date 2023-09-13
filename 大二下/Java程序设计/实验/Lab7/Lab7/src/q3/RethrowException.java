package q3;

public class RethrowException {
    public static void someMethod2() throws Exception {
        System.out.println("someMethod2().");
        throw new Exception("First Throw");
    }
    public static void someMethod() throws Exception {
        System.out.println("someMethod().");
        try
        {
            someMethod2();
        }
        catch(Exception e)
        {
            System.out.println("Rethrow the exception.");
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        try {
            someMethod();
        }
        catch(Exception e) {
            System.out.println("Exception in main.");
            e.printStackTrace();
        }
    }
}
