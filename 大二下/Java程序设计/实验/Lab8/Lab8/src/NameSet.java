import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public class NameSet {
    static Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) {
        while (true) {
            System.out.println("请输入一个名字序列，用空格分隔（end退出）：");

            String s = scanner.nextLine();
            if (s.equals("end"))
                break;
            else {
                String[] names = s.split(" ");
                List<String> list = Arrays.asList(names);
                printPerson(list);
            }
        }
    }

    public static void printPerson(List<String> list) {
        Set<String> set = new HashSet<String>(list);
        System.out.print("无重复的名字序列：");
        for (String name : set) {
            System.out.print(name + " ");
        }
        System.out.println("");
    }
}