import java.util.ArrayList;
import java.util.Scanner;
// 定义一个人的基本信息类
class Person {
    protected String id;    // 学号或者工号
    protected String name;  // 姓名

    // 构造函数
    public Person(String id, String name) {
        this.id = id;
        this.name = name;
    }
}

// 定义一个学生类，继承自Person类
class Student extends Person {
    protected String className; // 班级
    protected Course[] courses; // 学生所选的课程

    // 构造函数
    public Student(String id, String name, String className) {
        super(id, name);
        this.className = className;
    }

    // 自动选课方法，将所有必修课程添加到课程列表中
    public void autoSelectCourse(Course[] courses) {
        for (Course course : courses) {
            if (course instanceof RequiredCourse) {
                selectCourse(course);
            }
        }
    }

    // 手动选课方法，从选修课程中选择2门课程添加到课程列表中
    public void manualSelectCourse(Course[] courses) {
        int count = 0;
        for (Course course : courses) {
            if (course instanceof ElectiveCourse && count < 2) {
                selectCourse(course);
                count++;
            }
        }
    }

    // 选课方法，将指定的课程添加到课程列表中
    public void selectCourse(Course course) {
        if (courses == null) {
            courses = new Course[]{course};
        } else {
            int len = courses.length;
            Course[] newCourses = new Course[len + 1];
            System.arraycopy(courses, 0, newCourses, 0, len);
            newCourses[len] = course;
            courses = newCourses;
        }
    }

    // 打印学生的选课信息
    public void printCourseSelection() {
        System.out.println("学生信息：");
        System.out.println("学号：" + id);
        System.out.println("姓名：" + name);
        System.out.println("班级：" + className);
        System.out.println("已选课程：");
        if (courses == null) {
            System.out.println("无");
        } else {
            for (Course course : courses) {
                System.out.println(course.toString());
            }
        }
        System.out.println();
    }
}

// 定义一个课程类
class Course {
    protected String id;        // 课程编号
    protected String name;      // 课程名称
    protected double credit;    // 学分

    // 构造函数
    public Course(String id, String name, double credit) {
        this.id = id;
        this.name = name;
        this.credit = credit;
    }

    // toString方法，用于打印课程信息
    @Override
    public String toString() {
        return id + " " + name + " " + credit;
    }
}

// 定义必修课程类，继承自课程类
class RequiredCourse extends Course {
    // 构造函数
    public RequiredCourse(String id, String name, double credit) {
        super(id, name, credit);
    }
}

// 定义选修课程类，继承自课程类
class ElectiveCourse extends Course {
    public ElectiveCourse(String id, String name, double credit) {
        super(id, name, credit);
    }
}

// 定义选课系统类
public class College {
    public static void main(String[] args) {
// 创建四个学生信息
        Student stu1 = new Student("201801", "小明", "计算机科学与技术1班");
        Student stu2 = new Student("201802", "小红", "计算机科学与技术1班");
        Student stu3 = new Student("202101", "张三", "软件工程1班");
        Student stu4 = new Student("202102", "李四", "软件工程1班");
        // 创建四门课程信息
        Course c1 = new RequiredCourse("C001", "高等数学", 4.0);
        Course c2 = new RequiredCourse("C002", "大学英语", 3.0);
        Course c3 = new ElectiveCourse("C101", "计算机网络", 3.5);
        Course c4 = new ElectiveCourse("C102", "数据结构", 3.5);

        // 自动选课
        stu1.autoSelectCourse(new Course[]{c1, c2, c3, c4});
        stu2.autoSelectCourse(new Course[]{c1, c2, c3, c4});
        stu3.autoSelectCourse(new Course[]{c1, c2, c3, c4});
        stu4.autoSelectCourse(new Course[]{c1, c2, c3, c4});

        // 秘书手动选课
        stu1.manualSelectCourse(new Course[]{c3, c4});
        stu2.manualSelectCourse(new Course[]{c3, c4});
        stu3.manualSelectCourse(new Course[]{c3, c4});
        stu4.manualSelectCourse(new Course[]{c3, c4});

        // 打印选课信息
        stu1.printCourseSelection();
        stu2.printCourseSelection();
        stu3.printCourseSelection();
        stu4.printCourseSelection();
    }
}