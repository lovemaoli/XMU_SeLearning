package exam;

//这是基础类
//11920192203642 袁佳哲

public class book 
{
	private String ISBN;
	private String bookName;
	private String Status;
	private String chubanshe;
	
	
//	public String getBookNo() 
//	{
//		return bookNo;
//	}
//
//
//	public void setBookNo(String bookNo) {
//		this.bookNo = bookNo;
//	}


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


	public String getStatus() {
		return Status;
	}


	public void setStatus(String status) {
		Status = status;
	}


	public String getChubanshe() {
		return chubanshe;
	}


	public void setChubanshe(String chubanshe) {
		this.chubanshe = chubanshe;
	}
	
	


//	public static String getNewBookNo(String BookType, String BookNo)
//	{
//        String newBookNo = "00001";
// 
//        if(BookNo != null && !BookNo.isEmpty()){
//            int newBook = Integer.parseInt(BookNo) + 1;
//            BookNo = String.format(BookType + "%05d", newBook);
//        }
// 
//        return newBookNo;
//    }
}
