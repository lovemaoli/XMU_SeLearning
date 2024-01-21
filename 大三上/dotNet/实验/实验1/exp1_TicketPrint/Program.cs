using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TicketPrint
{
    class McDonaldsReceipt
    {
        class Restaurant
        {
            public string Name { get; }
            public string Phone { get; }
            public string Address { get; }

            public Restaurant(string name, string phone, string address)
            {
                Name = name;
                Phone = phone;
                Address = address;
            }
        }
        class Item
        {
            public string Name { get; }
            public double Price { get; }
            public int Quantity { get; }

            public Item(string name, double price, int quantity)
            {
                Name = name;
                Price = price;
                Quantity = quantity;
            }
        }
        class Customer
        {
            public string Name { get; }
            public string Phone { get; }
            public string Address { get; }

            public Customer(string name, string phone, string address)
            {
                Name = name;
                Phone = phone;
                Address = address;
            }
        }
        static string padLeftEx(string str, int totalByteCount) //解决中英文混排问题
        {
            Encoding coding = Encoding.GetEncoding("UTF-8");
            int dcount = 0;
            foreach (char ch in str.ToCharArray())
            {
                if(coding.GetByteCount(ch.ToString())>1)
                    dcount++;
            }
            string w = str.PadRight(totalByteCount - dcount);
            return w;
        }
        static string padRightEx(string str, int totalByteCount) //解决中英文混排问题
        {
            Encoding coding = Encoding.GetEncoding("UTF-8");
            int dcount = 0;
            foreach (char ch in str.ToCharArray())
            {
                if (coding.GetByteCount(ch.ToString()) > 1)
                    dcount++;
            }
            string w = str.PadLeft(totalByteCount - dcount);
            return w;
        }
        static void Main(string[] args)
        {
            // 初始化小票商品
            List<Item> items = new List<Item>
            {
                new Item("巨无霸汉堡", 25.5, 2),
                new Item("薯条", 8, 1),
                new Item("可乐", 6, 2),
                new Item("麦旋风", 8, 1)
            };

            string note = "外卖订单，请速送";
            Restaurant restaurant = new Restaurant("麦当劳厦大分店", "000-111-2222", "123 翔安大学, Xiamen");
            Customer customer = new Customer("杰哥", "114-514-1919", "国光13 906, Xiamen");

            DateTime orderTime = new DateTime(2023, 9, 19, 12, 30, 0);
            DateTime deliveryTime = new DateTime(2023, 9, 19, 13, 0, 0);

            PrintReceipt(note, restaurant, items, customer, 50.0, orderTime, deliveryTime);
        }

        static void PrintReceipt(string note, Restaurant restaurant, List<Item> items,
            Customer customer, double discount, DateTime orderTime, DateTime deliveryTime)
        {
            Console.WriteLine("***************** 麦当劳小票 ****************");
            Console.WriteLine($"订单时间：{orderTime:yyyy-MM-dd HH:mm}");
            Console.WriteLine($"送达时间：{deliveryTime:yyyy-MM-dd HH:mm}");
            Console.WriteLine("---------------------------------------------");
            Console.WriteLine($"分店名称：{restaurant.Name}");
            Console.WriteLine($"联系电话：{restaurant.Phone}");
            Console.WriteLine($"地址：{restaurant.Address}");
            Console.WriteLine("---------------------------------------------");
            Console.WriteLine($"顾客姓名：{customer.Name}");
            Console.WriteLine($"联系电话：{customer.Phone}");
            Console.WriteLine($"送货地址：{customer.Address}");
            Console.WriteLine("---------------------------------------------");
            Console.WriteLine("订单详情：");
            Console.WriteLine("---------------------------------------------");
            double total = 0.0;
            //名称左对齐-22 数量右对齐5 单价右对齐9 小计右对齐9
            Console.WriteLine($"{padLeftEx("名称",22)}{padRightEx("数量",5)}{padRightEx("单价",9)}{padRightEx("小计",9)}");
            Console.WriteLine(new string('-', 45));

            foreach (var item in items)
            {
                string itemName = item.Name;
                int itemQuantity = item.Quantity;
                double itemPrice = item.Price;
                double itemTotalPrice = item.Price * item.Quantity;
                Console.WriteLine($"{padLeftEx(itemName.ToString(),22)}{padRightEx("x"+itemQuantity.ToString(),5)}{padRightEx($"{itemPrice:C}",9)}{padRightEx($"{itemTotalPrice:C}",9)}");
                total += itemTotalPrice;
            }

            Console.WriteLine(new string('-', 45));
            Console.WriteLine($"{padRightEx($"总计金额：{total:C}",45)}");
            Console.WriteLine($"{padRightEx($"优惠金额：{discount:C}",45)}");
            double finalTotal = total - discount;
            Console.WriteLine($"{padRightEx($"实付金额：{finalTotal:C}",45)}");
            Console.WriteLine(new string('-', 45));
            Console.WriteLine($"{padRightEx($"备注：{note}",45)}");
            Console.WriteLine("*********************************************");
            Console.WriteLine("感谢您的订餐，欢迎再次光临麦当劳！");
        }
    }
}
