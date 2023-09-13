/**@author 袁佳哲 **/
package lab6;

import java.util.Scanner;
import java.util.ArrayList;

public class carTeam 
{
	private static Scanner scan = new Scanner(System.in);
	
	static ArrayList<vehicle> carList = new ArrayList<>();
	
	//构造函数
//	public carTeam()
//	{
//		ArrayList<vehicle> carList = new ArrayList<>();	
//	}
	
	//新增车辆
	public static void addVehicle() throws Exception 
	{
		//提示信息
		System.out.println("请输入车辆信息，实例：\n"
				+"\t小汽车 丰田 红色 4 2007 2厢\n"
				+"\t卡车 雷诺 红色 3.5 2008\n"
				+"结束新增，请输入end");
		
		String inputString = scan.nextLine();
		while(!inputString.equals("end"))
		{
			//空格分隔输入信息
			String[] inputs = inputString.split("[ ]+");
			if(inputs[0].equals("小汽车"))
			{
				//多次出现错误，先是java.lang.ClassNotFoundException，把forName里改成lab.car就解决了
				//然后是利用自动修正功能加上强制类型转换和方法名后面的throws Exception
				//最后是wrong number of arguments，经过百度，把newInstance里加上(Object)就解决了
				car newCar = (car) Class.forName("lab6.car").getConstructor(String[].class).newInstance((Object)inputs);
				carList.add(newCar);
				System.out.println("创建成功");
			}
			else if(inputs[0].equals("卡车"))
			{
				truck newTruck = (truck) Class.forName("lab6.truck").getConstructor(String[].class).newInstance((Object)inputs);
				carList.add(newTruck);
				System.out.println("创建成功");
			}
			else
			{
				System.out.println("第一个应为小汽车或卡车\n");
				System.out.println("创建不成功");
			}
			//多次输入
			System.out.println("请输入车辆信息，实例：\n"
					+"\t小汽车 丰田 红色 4 2007 2厢\n"
					+"\t卡车 雷诺 红色 3.5 2008\n"
					+"结束新增，请输入end");
			inputString = scan.nextLine();
		}
	}
	
	//查询车辆
	public static void search()
	{
		//如果未添加过车辆，不能执行查询功能，防止bug
		if(carList.size() == 0)
		{
			System.out.println("当前车队为空，无法进行查询，请先添加车辆！");
			return;
		}
		
		System.out.println("请按照“类型 商标 颜色 出厂年”的顺序输入条件，若条件为空用“null”代替,两个示例:");
		System.out.println("\t小汽车 丰田 红色 2007");
		System.out.println("\tnull 丰田 null null");
		System.out.println("输入end返回上级菜单");
		
		String inputString = scan.nextLine();
		//用来存放查询结果
		ArrayList<vehicle> results = new ArrayList<>();
		while(!inputString.equals("end"))
		{
			String[] inputs = inputString.split("[ ]+");
			if((inputs[0].equals("小汽车") || inputs[0].equals("卡车") || inputs[0].equals("null")))
			{
				for(vehicle vehicles : carList)
				{
					if(
							(inputs[0].equals("null") || vehicles.getCarName().equals(inputs[0]))
							&& (inputs[1].equals("null") || vehicles.getBrand().equals(inputs[1]))
							&& (inputs[2].equals("null") || vehicles.getColor().equals(inputs[2]))
							&& (inputs[3].equals("null") || vehicles.getYear() == Integer.parseInt(inputs[3]))
						)
						results.add(vehicles);
				}
				System.out.printf("搜索到%d辆车,信息如下：\n",results.size());
				//打印结果列表
				for(vehicle vehicles : results)
				{
					//vehicles.printInfo();
					System.out.println(vehicles.toString());
				}
				System.out.print("\n");
			}
			else
			{
				System.out.println("没有搜索到相应的交通工具");
			}
			System.out.println("请按照“类型 商标 颜色 出厂年”的顺序输入条件，若条件为空用“null”代替,两个示例:");
			System.out.println("\t小汽车 丰田 红色 2007");
			System.out.println("\tnull 丰田 null null");
			System.out.println("输入end返回上级菜单");
			//下一次查询前清空结果列表
			results.clear();
			inputString = scan.nextLine();
		}
	}
	
	//显示所有车辆
	public static void printAll()
	{
		if(carList.size() == 0)
		{
			System.out.println("目前没有车！无法列出信息！");
			return;
		}
		
		System.out.println("目前有" + carList.size() + "辆车，信息如下：");
		for(vehicle vehicles : carList)
		{
			//vehicles.printInfo();
			System.out.println(vehicles.toString());
		}
		System.out.printf("\n");
	}
	
	//打印主菜单
	public static void printMenu()
	{
		System.out.println("请输入对应输入进行相应菜单操作：");
		System.out.println("1.	新增车辆");
		System.out.println("2.	查询车辆");
		System.out.println("3.	列出所有车辆");
		System.out.println("4.	结束程序");
	}
	
	public static void main(String[] args) throws Exception
	{
		String input;
		boolean flag = true;
		
		//用一个布尔型的变量来控制程序的重复运行
		while(flag)
		{
			printMenu();
			input = scan.nextLine();
			//如果输入的不是1-4，就发出提示并重复输入
			if(!input.equals("1") && !input.equals("2") && !input.equals("3") && !input.equals("4"))
				System.out.println("请输入1-4的整数");
			else
			{
				int choice = Integer.parseInt(input);
				switch(choice)
				{
				case 1:
					addVehicle();
					break;
					
				case 2:
					search();
					break;
					
				case 3:
					printAll();
					break;
					
				case 4:
					flag = false;
					break;
					
				}
			}
		}
		
		System.out.println("谢谢使用");
	}
}
