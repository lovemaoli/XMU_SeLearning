import java.util.Scanner;

public class UserInput {
    public static void main(String[] args) {
        String name, password, mail;
        name = inputName();
        password = inputPassword();
        mail = inputMail();
        System.out.println("用户名：" + name + " 邮箱：" + mail + " 密码：" + password);
    }

    public static String inputName() {
        System.out.println("请输入用户名（不能为空，只能由字母、数字和_组成，第一位不能为数字）");
        Scanner input = new Scanner(System.in);
        String name = input.nextLine();
        while (!name.matches("^(?!\\d)\\w*|\\d*|_*") || name.equals("")) {
            if (!name.matches("\\w*|\\d*|_*"))
                System.out.println("输入错误，请重新输入！（只能由字母、数字和_组成）");
            else if (name.equals(""))
                System.out.println("输入错误，请重新输入！（不能为空）");
            else if (!name.matches("^(?!\\d)"))
                System.out.println("输入错误，请重新输入！（第一位不能为数字）");
            name = input.nextLine();
        }
        return name;
    }

    public static String inputPassword() {
        System.out.println("请输入密码（不能为空，密码长度至少8位，由字母、数字、下划线组成）");
        Scanner input = new Scanner(System.in);
        String password = input.nextLine();
        while (!password.matches("([a-zA-Z0-9]|_){8,}") || password.equals("")) {
            if (!password.matches("\\w*|\\d*|_*"))
                System.out.println("输入格式错误，请重新输入！（只能由字母、数字和_组成）");
            else if (password.equals(""))
                System.out.println("输入格式错误，请重新输入！（不能为空）");
            else if (password.length() < 8)
                System.out.println("输入格式错误，请重新输入！（密码长度至少8位）");
            password = input.nextLine();
        }
        return password;
    }

    public static String inputMail() {
        System.out.println("请输入邮箱（不能为空，只能由字母、数字和_组成，需包含”@”符号。”@”符号后需要出现多个由”.”分割的词）");
        Scanner input = new Scanner(System.in);
        String mail = input.nextLine();
        while (!mail.matches("[a-zA-Z0-9]*@(([a-zA-Z0-9])+\\.)+[a-zA-Z0-9]+") || mail.equals("")) {
            if (!mail.contains("@"))
                System.out.println("输入格式错误，请重新输入！（需包含”@”符号）");
            else if (!mail.matches("(\\w|\\d|_|@|\\.)*"))
                System.out.println("输入格式错误，请重新输入！（只能由字母、数字和_组成）");
            else System.out.println("输入格式错误，请重新输入！（”@”符号后需要出现多个由”.”分割的词）");
            mail = input.nextLine();
        }
        return mail;
    }

}