package exam;

//这个是普通书类
//11920192203642 袁佳哲

public class normalBook extends book
{
	private int bookNo;
	private String ISBN;
	private String bookName;
	private String author;
	private String chubanshe;
	private String Status;
	
	
	public int getBookNo() {
		return bookNo;
	}
	public void setBookNo(int bookNo) {
		this.bookNo = bookNo;
	}
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
	public String getStatus() {
		return Status;
	}
	public void setStatus(String status) {
		Status = status;
	}
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	
	public normalBook(String[] inputs)
	{
		this.ISBN = inputs[1];
		this.bookName = inputs[2];
		this.author = inputs[3];
		this.chubanshe = inputs[4];
		Status = "未借出";
	}

	public String toString()
	{
		return String.format("%05d 书 %s %s %s %s %s", bookNo, ISBN, bookName, author, chubanshe, Status);
	}
}
