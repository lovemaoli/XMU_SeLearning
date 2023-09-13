package q4;

public class IllegalNameException extends Exception{
    public IllegalNameException() {
        super();
    }

    public IllegalNameException(String message) {
        super(message);
    }

    public IllegalNameException(String message, Throwable cause) {
        super(message, cause);
    }

    public IllegalNameException(Throwable cause) {
        super(cause);
    }
}
