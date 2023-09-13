package q2;

public class TestSomeClass {
    public static void main(String[] args) {
        //程序创建一个 q2.SomeClass 型的对象，并捕获由这个构造方法抛出的异常。
        try {
            SomeClass someClass = new SomeClass();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
