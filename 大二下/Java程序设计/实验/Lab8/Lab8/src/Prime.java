import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Prime {
    static Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) {
        while (true) {
            System.out.println("请输入一个大于1的整数（-1退出）：");
            try {
                int num = scanner.nextInt();
                if (num == -1)
                    return;
                else if (num < 0)
                    throw new Exception();
                else
                    calcDivisor(num);
            } catch (Exception e) {
                System.err.println("输入错误，请重新输入");
            }
        }
    }
    public static void calcDivisor(int n) {
        Set<Integer> set = new HashSet<Integer>();
        for (int i = 2; i <= Math.sqrt(n); i++) {
            boolean flag = true;
            if (n % i == 0) {
                if (set.size() != 0) {
                    for (int s : set)
                        if (i % s == 0) {
                            flag = false;
                            break;
                        }
                }
                if (flag)
                    set.add(i);
            }
        }
        if (set.size() == 0) {
            System.out.println(n + "是质数，" + "其因子为1 " + n);
            System.out.printf("%n");
        } else {
            System.out.print(n + "不是质数，其质因子为");
            for (int s : set)
                System.out.print(s + " ");
            System.out.println();
        }
    }
}