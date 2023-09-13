import java.util.Scanner;

class Student {
    private String id;
    private String name;
    private String className;
    private String phoneNumber;

    public Student(String id, String name, String className, String phoneNumber) {
        this.id = id;
        this.name = name;
        this.className = className;
        this.phoneNumber = phoneNumber;
    }

    public Student(String id, String name, String className) {
        this(id, name, className, null);
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getClassName() {
        return className;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }
}

class Course {
    private String courseCode;
    private String courseName;

    public Course(String courseCode, String courseName) {
        this.courseCode = courseCode;
        this.courseName = courseName;
    }

    public String getCourseCode() {
        return courseCode;
    }

    public String getCourseName() {
        return courseName;
    }
}

public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // 获取学生信息
        System.out.println("请输入学生1的信息：");
        System.out.print("学号：");
        String id1 = scanner.nextLine();
        System.out.print("姓名：");
        String name1 = scanner.nextLine();
        System.out.print("班级：");
        String className1 = scanner.nextLine();
        System.out.print("电话：");
        String phoneNumber1 = scanner.nextLine();
        Student student1 = new Student(id1, name1, className1, phoneNumber1);

        System.out.println("请输入学生2的信息：");
        System.out.print("学号：");
        String id2 = scanner.nextLine();
        System.out.print("姓名：");
        String name2 = scanner.nextLine();
        System.out.print("班级：");
        String className2 = scanner.nextLine();
        System.out.print("电话：");
        String phoneNumber2 = scanner.nextLine();
        Student student2 = new Student(id2, name2, className2, phoneNumber2);

        // 获取课程信息
        System.out.println("请输入课程1的信息：");
        System.out.print("课程编号：");
        String courseCode1 = scanner.nextLine();
        System.out.print("课程名称：");
        String courseName1 = scanner.nextLine();
        Course course1 = new Course(courseCode1, courseName1);

        System.out.println("请输入课程2的信息：");
        System.out.print("课程编号：");
        String courseCode2 = scanner.nextLine();
        System.out.print("课程名称：");
        String courseName2 = scanner.nextLine();
        Course course2 = new Course(courseCode2, courseName2);

        // 输出选课结果以及成绩
        System.out.println("学生" + student1.getName() + "选了" + course1.getCourseName() + "，成绩为：90");
        System.out.println("学生" + student2.getName() + "选了" + course2.getCourseName() + "，成绩为：85");

        scanner.close();
    }
}
