// Fig. 27.16: TicTacToeClientTest.java
// Test class for Tic-Tac-Toe client.
import javax.swing.JFrame;

public class TicTacToeClientTest {
    public static void main(String[] args) {
        TicTacToeClient application; // declare client application

        // if no command line args
        if (args.length == 0)
            application = new TicTacToeClient("127.0.0.1"); // localhost
        else
            application = new TicTacToeClient(args[0]); // use args

        application.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    } // end main
} // end class TicTacToeClientTest