using System;
using System.Collections.Generic;
using System.Linq;


namespace LinQSample
{
    public class QueryVMethodSyntax
    {
        public IEnumerable<int> EvenNumsQuery1(int[] numbers)
        {
            var evenNumbersQuery =
                from number in numbers
                where number % 2 == 0
                orderby number
                select number;

            return evenNumbersQuery;
        }

        public IEnumerable<int> EvenNumsQuery2(int[] numbers)
        {
            // 使用方法语法，从整数数组中筛选出偶数并进行排序
            var evenNumbersQuery = numbers.Where(number => number % 2 == 0).OrderBy(number => number);

            return evenNumbersQuery;
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            
            // Specify the data source.
            

            Console.WriteLine(new string('*', 60));

            int[] scores = { 96, 64, 98, 81, 60 };
            // 使用LINQ查询表达式，从整数数组scores中筛选出大于80的分数，并输出
            //begin
            var highScoresQuery2 =
                from score in scores
                where score > 80
                select score;

            foreach(int s in highScoresQuery2)
            {
                Console.Write(s + ", ");
            }
            Console.WriteLine();

            //end
           
            //排序
            IEnumerable<string> highScoresQuery =
                from score in scores
                where score > 80
                orderby score descending  //ascending
                select $"The score is {score}";   //select score;

            foreach(string s in highScoresQuery)
            {
                Console.Write(s + "\n");
            }
            Console.WriteLine();
            Console.WriteLine(new string('*',60));


            //根据上下文，使用LINQ查询表达式，声明一个整数变量highSourceCount表示大于80的分数的数量
            //begin
            var highScoreCount =
                (from score in scores
                 where score > 80
                 select score).Count();


            //end
            Console.Write(highScoreCount.ToString());
            Console.WriteLine();


            //使用LINQ查询，从名为scores的整数集合中选择所有大于80的分数，并将结果存储在highScoreQuery1中
            //begin
            var highScoreQuery1 =
                from score in scores
                where score > 80
                select score;

            //end
                
            int count1 = highScoreQuery1.Count();

            Console.WriteLine(count1.ToString());

            string[] names = { "Svetlana Omelchenko", "Claire O'Donnell", "Sven Mortensen", "Cesar Garcia" };
            //使用LINQ查询，获取上述names数组中每个名字的第一个名字
            //begin
            var queryFirstNames =
                from name in names
                select name.Split(' ')[0];


            //end
            foreach (string s in queryFirstNames)
            {
                Console.Write(s + " ");
            }
            Console.WriteLine();

            

            QueryVMethodSyntax qv = new QueryVMethodSyntax();
            int[] numbers = { 5, 10, 8, 3, 6, 12, 9, 112, 4 };
            IEnumerable<int> query = qv.EvenNumsQuery1(numbers);

            foreach (int i in query)
            {
                Console.Write(i + " ");
            }
            Console.WriteLine();

            IEnumerable<int> query2 = qv.EvenNumsQuery2(numbers);

            foreach (int i in query2)
            {
                Console.Write(i + " ");
            }
            Console.WriteLine();
        }
    }
}