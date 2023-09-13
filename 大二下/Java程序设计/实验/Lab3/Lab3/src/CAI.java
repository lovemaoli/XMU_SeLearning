import java.security.SecureRandom; // 导入 SecureRandom 类
import java.util.Scanner;
public class CAI {
    private static final SecureRandom rnd = new SecureRandom(); // 随机数生成器
    private static final Scanner scan = new Scanner(System.in);

    private static int give_question() // 出题函数，返回答案
    {
        int a = 1 + rnd.nextInt(10); // 随机生成两个1~10之间的整数
        int b = 1 + rnd.nextInt(10);
        System.out.printf("How much is %d times %d?\n",a, b);
        return a * b;
    }

    public static void main(String[] args)
    {
        System.out.println("This is CAI system, input \"-1\" to quit.");
        while(true)
        {
            int answer = give_question(); // 出题
            int input = scan.nextInt();
            if(input == answer) // 判断答案是否正确
            {
                System.out.println("Very Good!");
            }
            else if(input == -1)
                break;
            else {
                do // 答案不正确，循环提示输入直到回答正确
                {
                    System.out.println("No. Please try again.");
                    input = scan.nextInt();
                }
                while(input != answer);
                System.out.println("Very Good!");
            }
        }
        System.out.println("See you next time!");
    }
}
