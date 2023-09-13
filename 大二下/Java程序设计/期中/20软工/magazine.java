package exam;

//import java.lang.reflect.InvocationTargetException;
import java.util.Scanner;

//这个是杂志类
//11920192203642 袁佳哲

public class magazine extends book
{
	private Scanner scan = new Scanner(System.in);
	private int bookNo;
	private String ISBN;
	private String bookName;
	private String chubanshe;
	private String Status;
	private int year;
	private int no;
	
	
	public String getISBN() {
		return ISBN;
	}

	public void setISBN(String iSBN) {
		ISBN = iSBN;
	}

	public String getBookName() {
		return bookName;
	}

	public void setBookName(String bookName) {
		this.bookName = bookName;
	}

	public String getChubanshe() {
		return chubanshe;
	}

	public void setChubanshe(String chubanshe) {
		this.chubanshe = chubanshe;
	}

	public int getBookNo() {
		return bookNo;
	}

	public void setBookNo(int bookNo) {
		this.bookNo = bookNo;
	}

	public magazine(String[] inputs)
	{
		bookNo++;
		ISBN = inputs[1];
		bookName = inputs[2];
		
		try
		{
			year = Integer.parseInt(inputs[3]);
		}
		catch(Exception e)
		{
			System.out.println("年份必须为整数！请重新输入");
			while(!scan.hasNextInt())
			{
				System.out.println("年份必须为整数！请重新输入");
				scan.next();
			}
			year = scan.nextInt();
		}
		
		try
		{
			no = Integer.parseInt(inputs[4]);
		}
		catch(Exception e)
		{
			System.out.println("编号必须为整数！请重新输入");
			while(!scan.hasNextInt())
			{
				System.out.println("编号必须为整数！请重新输入");
				scan.next();
			}
			no = scan.nextInt();
		}
		
		chubanshe = inputs[5];
		Status = "未借出";
	}
	
	public int getYear() {
		return year;
	}
	public void setYear(int year) {
		this.year = year;
	}
	public int getNo() {
		return no;
	}
	public void setNo(int no) {
		this.no = no;
	}
	
	public String toString()
	{
		return String.format("%05d 杂志 %s %s %d %d %s %s", bookNo, ISBN, bookName, year, no, chubanshe, Status);
	}
}
