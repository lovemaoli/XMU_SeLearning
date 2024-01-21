using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LINQDrill
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine();
            Console.WriteLine("Hello, World!");

            
            // Create a data source by using a collection initializer.
             List<Student> students = new List<Student>
            {
                new Student {First="Svetlana", Last="Omelchenko", ID=111, Scores= new List<int> {97, 92, 81, 60}},
                new Student {First="Claire", Last="O'Donnell", ID=112, Scores= new List<int> {75, 84, 91, 39}},
                new Student {First="Sven", Last="Mortensen", ID=113, Scores= new List<int> {88, 94, 65, 91}},
                new Student {First="Cesar", Last="Garcia", ID=114, Scores= new List<int> {97, 89, 85, 82}},
                new Student {First="Debra", Last="Garcia", ID=115, Scores= new List<int> {35, 72, 91, 70}},
                new Student {First="Fadi", Last="Fakhouri", ID=116, Scores= new List<int> {99, 86, 90, 94}},
                new Student {First="Hanying", Last="Feng", ID=117, Scores= new List<int> {93, 92, 80, 87}},
                new Student {First="Hugo", Last="Garcia", ID=118, Scores= new List<int> {92, 90, 83, 78}},
                new Student {First="Lance", Last="Tucker", ID=119, Scores= new List<int> {68, 79, 88, 92}},
                new Student {First="Terry", Last="Adams", ID=120, Scores= new List<int> {99, 82, 81, 79}},
                new Student {First="Eugene", Last="Zabokritski", ID=121, Scores= new List<int> {96, 85, 91, 60}},
                new Student {First="Michael", Last="Tucker", ID=122, Scores= new List<int> {94, 92, 91, 91}}
            };

            //第1次测试分数大于90
            //从students集合中筛选出分数的第一个元素大于或等于90的学生，并将它们存储在Query1变量中，在下方编写代码
            //begin
            var Query1 = from student in students
                         where student.Scores[0] > 90
                         select student;

            //end
            
            foreach (Student student in Query1)
            {
                Console.WriteLine("{0}:{1} {2}",student.ID, student.First ,student.Last);
            }
            Console.WriteLine("============================================================================");

            //第1次测试分数大于90 并且 所有测试都高于80
            IEnumerable<Student> Query2 = from student in students
                                          where student.Scores[0] >= 90 && student.Scores.Min() >80
                                          select student;

            foreach (Student student in Query2)
            {
                Console.WriteLine("{0}:{1} {2}", student.ID, student.First, student.Last);
            }

            Console.WriteLine("============================================================================");

            IEnumerable<IGrouping<char, Student>> Query3 =
                from student in students
                group student by student.Last[0];

            foreach (IGrouping<char,Student> studentgroup in Query3)
            {
                Console.WriteLine(studentgroup.Key);
                foreach (Student student in studentgroup)
                {
                    Console.WriteLine("{0}:{1} {2}", student.ID, student.First, student.Last);
                }
                
            }
            Console.WriteLine("============================================================================");

            //将学生对象按照姓氏的首字母进行分组，并按照首字母升序排序，最终将分组的结果存储在Query4变量中,在下方编写代码
            //begin
            var Query4 = from student in students
                         group student by student.Last[0] into studentGroup
                         orderby studentGroup.Key
                         select studentGroup;



            //end

            foreach (IGrouping<char, Student> studentgroup in Query4)
            {
                Console.WriteLine(studentgroup.Key);
                foreach (Student student in studentgroup)
                {
                    Console.WriteLine("{0}:{1} {2}", student.ID, student.First, student.Last);
                }

            }
            Console.WriteLine("============================================================================");

            // studentQuery5 is an IEnumerable<string>
            // This query returns those students whose
            // first test score was higher than their
            // average score.
            // let 的使用

            //找出那些前四门课程的平均分低于第一门课程分数的学生，然后将这些学生的姓和名连接成一个字符串，并将结果存储在studentQuery5变量中,在下方编写代码
            //begin
            var studentQuery5 =
                from student in students
                let firstScore = student.Scores[0]
                let averageScore = student.Scores.Skip(1).Average()
                where averageScore < firstScore
                select $"{student.Last} {student.First}";



            //end 

            foreach (string s in studentQuery5)
            {
                Console.WriteLine(s);
            }

            Console.WriteLine("============================================================================");

            //计算所有学生四次测试分数和的平均分
            var studentQuery6 =
                from student in students
                let totalScore = student.Scores[0] + student.Scores[1] +
                    student.Scores[2] + student.Scores[3]
                select totalScore;

            double averageScores = studentQuery6.Average();
            Console.WriteLine("Class average score = {0}", averageScores);

            // Output:
            // Class average score = 334.166666666667

            Console.WriteLine("============================================================================");
            //let的使用
            var studentQuery8 =
                from student in students
                let x = student.Scores[0] + student.Scores[1] +
                    student.Scores[2] + student.Scores[3]
                where x > averageScores
                orderby x descending
                select new { id = student.ID, score = x };

            var lastItem = studentQuery8.LastOrDefault();
            foreach (var item in studentQuery8)
            {
                if (item.Equals(lastItem))
                {
                    Console.Write("Student ID: {0}, Score: {1}", item.id, item.score);
                }
                else
                {
                    Console.WriteLine("Student ID: {0}, Score: {1}", item.id, item.score);
                }
            }

        }
    }
    
    public class Student
    {
        public string First { get; set; }
        public string Last { get; set; }
        public int ID { get; set; }
        public List<int> Scores;
    }
}