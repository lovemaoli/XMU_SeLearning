public class Test extends TT{
    public static void main(String[] args) {
        Test tmp = new Test("happy");
    }
    Test(String s){
        super(s);
        System.out.println("how do you do?");
    }
    Test(){
        this("I am Tom");
    }
}
class TT{
    TT(String s){
        this();
        System.out.println("I am "+s);
    }
    TT(){
        System.out.println("what a pleasure!");
    }
}
