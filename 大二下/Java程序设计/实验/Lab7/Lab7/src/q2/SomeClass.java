package q2;

//定义一个 q2.SomeClass 类，它在构造方法中抛出异常。
public class SomeClass {
    public SomeClass() throws Exception {
        throw new Exception("构造方法失败");
    }
}
