using System;

namespace SortDemo
{
    internal class SortPrensentaion
    {
        static int count = 1;
        static void Main(string[] args)
        {
            //输入数组
            Console.WriteLine("请输入数组元素，以空格分隔：");
            string[] input = Console.ReadLine().Split(' ');
            int[] arr;
            //没有读入数字
            if (input[0] == "")
            {
                //展示默认数组
                arr = new int[] { 8, 7, 3, 1, 9, 4, 2, 6, 5 };
                Console.WriteLine("默认数组：");
                PrintArray(arr,0,8);
            }
            else
            {
                arr = new int[input.Length];
                for (int i = 0; i < input.Length; i++)
                {
                    arr[i] = int.Parse(input[i]);
                }
            }
            //检查输入是否合法，是否有重复元素

            for (int i = 0; i < arr.Length; i++)
            {
                //检查是否有超过99的数
                if (arr[i] > 99)
                {
                    Console.WriteLine("数组中不能有大于99的数，否则不便于展示排序过程！");
                    return;
                }
                for (int j = i + 1; j < arr.Length; j++)
                {
                    if (arr[i] == arr[j])
                    {
                        Console.WriteLine("数组中不能有重复元素，否则不便于展示排序过程！");
                        return;
                    }
                }
            }

            Console.WriteLine();
            MergeSort(arr, 0, arr.Length - 1);
            Console.WriteLine("排序后的数组:");
            PrintArray(arr, 0, arr.Length - 1);
        }
        //以表格形式输出数组
        static void PrintArray(int[] arr, int left, int right)
        {
            int length = right - left + 1;
            for (int i = 0; i < length; i++) Console.Write("+----");
            Console.WriteLine("+");
            for (int i = left; i <= right; i++) Console.Write($"|{arr[i],3:00} ");
            Console.WriteLine("|");
            for (int i = 0; i < length; i++) Console.Write("+----");
            Console.WriteLine("+");
        }
        //快速排序
        static void MergeSort(int[] arr, int left, int right)
        {
            if (left >= right)return;
            int mid = (left + right)/2;
            MergeSort(arr, left, mid);
            MergeSort(arr, mid + 1, right);

            Console.WriteLine();
            Console.WriteLine($"----------------第{count}次排序----------------");
            count++;
            Console.WriteLine("左数组为:");
            PrintArray(arr, left, mid);
            Console.WriteLine("右数组为:");
            PrintArray(arr, mid + 1, right);

            int[] result = new int[right-left+1];
            int k = 0, i = left, j = mid + 1;

            while (i <= mid && j <= right)
            {
                if (arr[i] <= arr[j])
                {
                    Console.WriteLine($"i:{i}指向的数字较小 将 arr[i]:{arr[i]} 加入合并数组并且i++:");
                    result[k++] = arr[i++];
                    PrintArray(result, 0, k - 1);
                }
                else
                {
                    Console.WriteLine($"j:{j}指向的数字较小 将 arr[j]:{arr[j]} 加入合并数组并且j++:");
                    result[k++] = arr[j++];
                    PrintArray(result, 0, k - 1);
                }
            }
            if(i != mid || j != right)
            {
                Console.WriteLine("左或右数组合并完毕，将剩余元素加入到合并数组中.");
                while (i <= mid) result[k++] = arr[i++];
                while (j <= right) result[k++] = arr[j++];
                Console.WriteLine();
            }
            for (i = left, j = 0; i <= right; ++i, ++j)
            {
                arr[i] = result[j];
            }

            Console.WriteLine("本轮归并结束,排序后的数组为:");
            PrintArray(arr, left, right);
            Console.WriteLine();
        }
    }
}
