public class prime
{
    // 判断 n 是否为质数（方法一：从 2 到 n/2 逐一判断）
    private static boolean is_Prime_by_half(int n)
    {
        if(n == 1)
            return false; // 1 不是质数
        for(int i = 2; i <= n / 2; i++)
        {
            if(n % i == 0)
                return false; // 只要有一个因子，就不是质数
        }
        return true; // 未找到因子，是质数
    }
    // 判断 n 是否为质数（方法二：从 2 到 sqrt(n) 逐一判断）
    private static boolean is_Prime_by_sqrt(int n)
    {
        if(n == 1)
            return false;
        for(int i = 2; i <= Math.sqrt(n); i++)
        {
            if(n % i == 0)
                return false;
        }
        return true;
    }
    public static void main(String[] args)
    {
        System.out.println("使用n/2的方法判断质数：");
        int prime_num = 0; // 统计质数个数
        long startTime_1 = System.currentTimeMillis(); // 记录开始时间
        for(int i = 1; i < 10000; i++)
        {
            if(is_Prime_by_half(i))
            {
                System.out.printf("第%d个质数是%d\n", ++prime_num, i);
            }
        }
        long endTime_1 = System.currentTimeMillis(); // 记录结束时间
        long totalTime_1 = endTime_1 - startTime_1; // 计算用时
        System.out.printf("10000内一共有%d个质数\n", prime_num);

        System.out.println("使用sqrt(n)的方法判断质数：");
        prime_num = 0;
        long startTime_2 = System.currentTimeMillis();
        for(int i = 1; i < 10000; i++)
        {
            if(is_Prime_by_sqrt(i))
            {
                System.out.printf("第%d个质数是%d\n", ++prime_num, i);
            }
        }
        long endTime_2 = System.currentTimeMillis();
        long totalTime_2 = endTime_2 - startTime_2;
        System.out.printf("10000内一共有%d个质数\n", prime_num);
        System.out.println("方法一（n/2）共用时" + totalTime_1 + "ms");
        System.out.println("方法二（sqrt(n)）共用时" + totalTime_2 + "ms");
    }
}
