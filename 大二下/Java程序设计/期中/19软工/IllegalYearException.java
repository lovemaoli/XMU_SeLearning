package lab6;

@SuppressWarnings("serial")
public class IllegalYearException extends Exception 
{
	private String message;

	public IllegalYearException(String message) 
	{
		this.message = message;
	}
	
	public String toString()
	{
		return String.format("Cause: %s", message);
	}
	
}
