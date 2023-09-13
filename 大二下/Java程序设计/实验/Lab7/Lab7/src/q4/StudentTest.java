package q4;
//编写程序实现Student对象抛出这两种异常，在main方法中进行捕获并合理地处理。
public class StudentTest {
    public static void main(String[] args)
    {
        System.out.println("Run:");
        Student student = new Student("Jerry", "福建省厦门市");;
        System.out.println(student);
        try {
            student.setName("Huang Xu");
        } catch(IllegalNameException e) {
            e.printStackTrace();
        }
        try {
            student.setAddress("福建厦门");
        }
        catch(IllegalAddressException e) {
            e.printStackTrace();
        }
        System.out.println("Final:");
        System.out.println(student);
    }
}
