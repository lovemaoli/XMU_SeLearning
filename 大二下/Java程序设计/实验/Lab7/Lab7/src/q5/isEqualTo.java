package q5;

import java.util.Scanner;

public class isEqualTo {
    Scanner input = new Scanner(System.in);
    public static <T> boolean isEqualTo(T a, T b) {
        if (a.equals(b))
            return true;
        else
            return false;
    }
    public static void main(String[] args) {
        Integer a = 1, b = 2;
        String c = "abc", d = "啊哦鹅";
        Double f = 1.23, g = 1.23;
        Character h = '%', i = '$';
        String result;
        if (isEqualTo(a, b))
            result = "相等";
        else
            result = "不相等";
        System.out.println(a + "和" + b + result);
        if (isEqualTo(c, d))
            result = "相等";
        else
            result = "不相等";
        System.out.println(c + "和" + d + result);
        if (isEqualTo(f, g))
            result = "相等";
        else
            result = "不相等";
        System.out.println(f + "和" + g + result);
        if (isEqualTo(h, i))
            result = "相等";
        else
            result = "不相等";
        System.out.println(h + "和" + i + result);
    }


}