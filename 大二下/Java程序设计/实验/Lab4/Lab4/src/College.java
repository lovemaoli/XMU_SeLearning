import java.util.ArrayList;
import java.util.Scanner;

// 学生类，抽象类，包含学号、姓名和班级属性，以及选课方法
abstract class Student {
    private String id;
    private String name;
    private String className;
    private ArrayList<Course> courses = new ArrayList<>(); // 学生所选课程

    public Student(String id, String name, String className) {
        this.id = id;
        this.name = name;
        this.className = className;
    }

    public void selectCourse(Course course) {
        courses.add(course);
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

    public ArrayList<Course> getCourses() {
        return courses;
    }
}

// 本科生类，继承自学生类，增加一个构造函数
class Undergraduate extends Student {

    public Undergraduate(String id, String name, String className) {
        super(id, name, className);

    }

}

// 研究生类，继承自学生类，增加一个构造函数，以及导师属性
class Graduate extends Student {
    private String tutor;

    public Graduate(String id, String name, String className, String tutor) {
        super(id, name, className);
        this.tutor = tutor;
    }

    public String getTutor() {
        return tutor;
    }
}

// 课程类，包含编号、名称和学分属性
class Course {
    private String id;
    private String name;
    private int credit;
    private boolean iscompulsory;

    public Course(String id, String name, int credit,boolean comp) {
        this.id = id;
        this.name = name;
        this.credit = credit;
        this.iscompulsory = comp;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int getCredit() {
        return credit;
    }

    public boolean getIscompulsory() {
        return iscompulsory;
    }
}

public class College {
    public static void main(String[] args) {
        // 创建必修课程
        Course c1 = new Course("0001", "计算机组成原理", 3, true);
        Course c2 = new Course("0002", "计算机网络", 3, true);

        // 创建选修课程
        Course c3 = new Course("0003", "数据结构", 3, false);
        Course c4 = new Course("0004", "算法设计与分析", 3, false);

        // 创建学生信息
        Undergraduate u1 = new Undergraduate("001", "小明", "计算机科学与技术");
        Undergraduate u2 = new Undergraduate("002", "小红", "软件工程");
        Graduate g1 = new Graduate("003", "小张", "计算机应用", "赵老师");
        Graduate g2 = new Graduate("004", "小李", "计算机科学与技术", "刘老师");

        // 自动选课部分：为每个学生自动选修所有必修课
        u1.selectCourse(c1);
        u1.selectCourse(c2);
        u2.selectCourse(c1);
        u2.selectCourse(c2);
        g1.selectCourse(c1);
        g1.selectCourse(c2);
        g2.selectCourse(c1);
        g2.selectCourse(c2);

        // 秘书手动选课部分：为每个同学选修1-2门选修课
        Scanner scanner = new Scanner(System.in);

        System.out.println("请选择课程（输入课程编号）：");
        System.out.println("1. " + c3.getName() + "（" + c3.getCredit() + "学分）");
        System.out.println("2. " + c4.getName() + "（" + c4.getCredit() + "学分）");
        System.out.println("3. 均选中");
        System.out.print(u1.getName() + "：");
        int choice = scanner.nextInt();
        if (choice == 1) {
            u1.selectCourse(c3);
        } else if (choice == 2) {
            u1.selectCourse(c4);
        } else if (choice == 3) {
            u1.selectCourse(c3);
            u1.selectCourse(c4);
        }

        System.out.println("请选择课程（输入课程编号）：");
        System.out.println("1. " + c3.getName() + "（" + c3.getCredit() + "学分）");
        System.out.println("2. " + c4.getName() + "（" + c4.getCredit() + "学分）");
        System.out.println("3. 均选中");
        System.out.print(u2.getName() + "：");
        choice = scanner.nextInt();
        if (choice == 1) {
            u2.selectCourse(c3);
        } else if (choice == 2) {
            u2.selectCourse(c4);
        } else if (choice == 3) {
            u2.selectCourse(c3);
            u2.selectCourse(c4);
        }

        System.out.println("请选择课程（输入课程编号）：");
        System.out.println("1. " + c3.getName() + "（" + c3.getCredit() + "学分）");
        System.out.println("2. " + c4.getName() + "（" + c4.getCredit() + "学分）");
        System.out.println("3. 均选中");
        System.out.print(g1.getName() + "：");
        choice = scanner.nextInt();
        if (choice == 1) {
            g1.selectCourse(c3);
        } else if (choice == 2) {
            g1.selectCourse(c4);
        } else if (choice == 3) {
            g1.selectCourse(c3);
            g2.selectCourse(c4);
        }

        System.out.println("请选择课程（输入课程编号）：");
        System.out.println("1. " + c3.getName() + "（" + c3.getCredit() + "学分）");
        System.out.println("2. " + c4.getName() + "（" + c4.getCredit() + "学分）");
        System.out.println("3. 均选中");
        System.out.print(g2.getName() + "：");
        choice = scanner.nextInt();
        if (choice == 1) {
            g2.selectCourse(c3);
        } else if (choice == 2) {
            g2.selectCourse(c4);
        } else if (choice == 3) {
            g2.selectCourse(c3);
            g2.selectCourse(c4);
        }

        // 打印出每个学生的选课信息
        System.out.println("选课情况如下：");

        System.out.println(u1.getName() + "：");
        ArrayList<Course> courses = u1.getCourses();
        for (Course course : courses) {
            System.out.println(course.getName() + "（" + course.getCredit() + "学分）");
        }

        System.out.println(u2.getName() + "：");
        courses = u2.getCourses();
        for (Course course : courses) {
            System.out.println(course.getName() + "（" + course.getCredit() + "学分）");
        }

        System.out.println(g1.getName() + "：");
        courses = g1.getCourses();
        for (Course course : courses) {
            System.out.println(course.getName() + "（" + course.getCredit() + "学分）");
        }

        System.out.println(g2.getName() + "：");
        courses = g2.getCourses();
        for (Course course : courses) {
            System.out.println(course.getName() + "（" + course.getCredit() + "学分）");
        }
    }
}