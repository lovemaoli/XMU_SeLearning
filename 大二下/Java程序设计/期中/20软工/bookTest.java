package exam;

//这个是用来测试的类
//11920192203642 袁佳哲

import java.util.ArrayList;
import java.util.Scanner;

public class bookTest 
{
	static int No = 0;
	private static Scanner scan = new Scanner(System.in);
	static ArrayList<normalBook> normalBookList = new ArrayList<>();
	static ArrayList<magazine> magazineList = new ArrayList<>();
	
	//添加书
	public static void addBook() throws Exception
	{
		boolean flag = true;
		System.out.println("请按照以下格式输入：");
		System.out.println("\t书 ISBN 书名 作者 出版社");
		System.out.println("\t杂志 ISBN 杂志名 出版年 期号 出版社");
		System.out.println("如：");
		System.out.println("\t书 9787121340932 Java程序设计 约翰·刘易斯 电子工业出版社");
		System.out.println("\t杂志 9771009633001 中国国家地理 2021 1 中国国家地理出版社");
		System.out.println("其中出版年和期号必须为数字");
		
		String inputString = scan.nextLine();
		while(flag)
		{
			String[] inputs = inputString.split("[ ]+");
			if(inputs[0].equals("书"))
			{
				normalBook newnormalBook = (normalBook)Class.forName("exam.normalBook").getConstructor(String[].class).newInstance((Object)inputs);
				newnormalBook.setBookNo(++No);
				normalBookList.add(newnormalBook);
				System.out.println("创建成功");
			}
			else if(inputs[0].equals("杂志"))
			{
				magazine newMagazine = (magazine)Class.forName("exam.magazine").getConstructor(String[].class).newInstance((Object)inputs);
				newMagazine.setBookNo(++No);
				magazineList.add(newMagazine);
				System.out.println("创建成功");
			}
			else
			{
				System.out.println("第一个应为书或杂志\n");
				System.out.println("创建失败");
			}
			System.out.println("是否继续录入？（是/否）");
			inputString = scan.nextLine();
			if(inputString.equals("是"))
			{
				System.out.println("请按照以下格式输入：");
				System.out.println("\t书 ISBN 书名 作者 出版社");
				System.out.println("\t杂志 ISBN 杂志名 出版年 期号 出版社");
				System.out.println("如：");
				System.out.println("\t书 9787121340932  Java程序设计 约翰·刘易斯 电子工业出版社");
				System.out.println("\t杂志 9771009633001 中国国家地理 2021 1 中国国家地理出版社");
				System.out.println("其中出版年和期号必须为数字");
				inputString = scan.nextLine();
			}
			else if(inputString.equals("否"))
			{
				flag = false;
				break;
			}
		}
	}
	
	//查询书
	public static void search()
	{
		//如果未录入过信息，不能执行查询功能，防止bug
		if(normalBookList.size() + magazineList.size() == 0)
		{
			System.out.println("当前没有书，无法进行查询，请先录入书籍信息！");
			return;
		}
		
		System.out.println("请按照以下格式输入查询信息：");
		System.out.println("\t书 ISBN 书名 作者 出版社");
		System.out.println("\t杂志 ISBN 杂志名 出版年 期号 出版社");
		System.out.println("如：");
		System.out.println("\t书 9787121340932  Java程序设计 约翰·刘易斯 电子工业出版社");
		System.out.println("\t杂志 9771009633001 中国国家地理 2021 1 中国国家地理出版社");
		System.out.println("其中空的字段均可用null代替 ");
		
		String inputString = scan.nextLine();
		
		ArrayList<book> results = new ArrayList<>();
		
		String[] inputs = inputString.split("[ ]+");
		
		if(inputs[0].equals("书"))
		{
			for(normalBook eachBook : normalBookList)
			{
				if(
						(inputs[1].equals("null") || eachBook.getISBN().equals(inputs[1]))
						&& (inputs[2].equals("null") || eachBook.getBookName().equals(inputs[2]))
						&& (inputs[3].equals("null") || eachBook.getAuthor().equals(inputs[3]))
						&& (inputs[4].equals("null") || eachBook.getChubanshe().equals(inputs[4]))
					)
					results.add(eachBook);
			}
		}
		else if(inputs[0].equals("杂志"))
		{
			for(magazine eachBook : magazineList)
			{
				if(
						(inputs[1].equals("null") || eachBook.getISBN().equals(inputs[1]))
						&& (inputs[2].equals("null") || eachBook.getBookName().equals(inputs[2]))
						&& (inputs[3].equals("null") || eachBook.getYear() == Integer.parseInt(inputs[3]))
						&& (inputs[4].equals("null") || eachBook.getNo() == Integer.parseInt(inputs[4])
						&& (inputs[5].equals("null") || eachBook.getChubanshe().equals(inputs[5])))
					)
					results.add(eachBook);
			}
		}
		
		//如果之前查到了书，就添加到results里
		//所以用results为空来代表没有查询结果
		if(results.size() > 0)
		{
			System.out.printf("搜索到%d本书,信息如下：\n",results.size());
			//打印结果列表
			for(book eachBook : results)
			{
				//vehicles.printInfo();
				System.out.println(eachBook.toString());
			}
			System.out.print("\n");
		}
		else
		{
			System.out.println("没找到任何书籍！");
			return;
		}
			
		
		//results.clear();
	}
	
	//显示所有书
	public static void printAllBook()
	{
		if(normalBookList.size() + magazineList.size() == 0)
		{
			System.out.println("没有书！无法列出信息！");
			return;
		}
		
		System.out.println("目前有" + (normalBookList.size() + magazineList.size()) + "本书，信息如下：");
		for(normalBook eachbook : normalBookList)
		{
			System.out.println(eachbook.toString());
		}
		for(magazine eachbook : magazineList)
		{
			System.out.println(eachbook.toString());
		}
		System.out.printf("\n");
	}
	
	//打印主菜单
	public static void printMenu()
	{
		System.out.println("请输入命令编号：");
		System.out.println("a.	录入");
		System.out.println("b.	查询");
		System.out.println("c.	查看书列表");
		System.out.println("d.	退出");
	}
	
	public static void main(String[] args) throws Exception
	{
		String input;
		boolean flag = true;
		
		while(flag)
		{
			printMenu();
			input = scan.nextLine();
			if(!input.equals("a") && !input.equals("b") && !input.equals("c") && !input.equals("d"))
				System.out.println("输入错误，请输入a-d的字母");
			else
			{
				char choice = input.charAt(0);
				switch(choice)
				{
				case 'a':
					addBook();
					break;
				case 'b':
					search();
					break;
				case 'c':
					printAllBook();
					break;
				case 'd':
					flag = false;
					break;
				}
			}
		}
		System.out.println("谢谢使用");
	}
}
