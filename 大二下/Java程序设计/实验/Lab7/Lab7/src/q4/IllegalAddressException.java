package q4;

public class IllegalAddressException extends Exception{
    public IllegalAddressException() {
        super();
    }

    public IllegalAddressException(String message) {
        super(message);
    }

    public IllegalAddressException(String message, Throwable cause) {
        super(message, cause);
    }

    public IllegalAddressException(Throwable cause) {
        super(cause);
    }
}
