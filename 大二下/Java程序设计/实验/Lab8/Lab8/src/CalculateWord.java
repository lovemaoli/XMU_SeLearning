import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class CalculateWord {
    static Scanner scanner = new Scanner(System.in);
    static boolean flag = false;
    static int num = 0;

    public static void main(String[] args) {
        while (true) {
            System.out.println("输入一句英文(end结束):");
            String s = scanner.nextLine().trim();
            if (s.equals("end"))
                break;
            else {
                Map<String, Integer> map = createMap(s);
                calculate(map);
            }
        }
    }
    // 创建map
    public static Map<String, Integer> createMap(String s) {
        Map<String, Integer> count = new HashMap<String, Integer>();
        s = s.replaceAll("\\pP", " ");// 去除标点符号
        String[] sentence = s.split(" ");
        for (String beforeWord : sentence) {
            String word = beforeWord.toLowerCase();
            if (count.containsKey(word)) {
                int current_count = count.get(word);
                count.put(word, current_count + 1);
            } else
                count.put(word, 1);
        }
        return count;
    }
    // 统计
    public static void calculate(Map<String, Integer> count) {
        // 初始化
        flag = false;
        num = 0;
        // 统计
        count.forEach((key, value) -> {
            if (value > 1) {
                flag = true;
                num++;
            }
        });
        if (flag) {
            System.out.println("有重复的单词统计:");
            System.out.println("单词\t\t\t次数");
            count.forEach((key, value) -> {
                if (value > 1) {
                    System.out.println(String.format("%-10s", key) + value);
                }
            });
            System.out.println("重复单词个数:" + num);
            System.out.println();
        } else
            System.out.println("无重复单词");
    }
}
