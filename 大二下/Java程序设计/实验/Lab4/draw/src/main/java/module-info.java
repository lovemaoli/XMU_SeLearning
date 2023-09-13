module com.example.draw {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.draw to javafx.fxml;
    exports com.example.draw;
}