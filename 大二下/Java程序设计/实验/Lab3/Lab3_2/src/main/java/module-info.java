module com.example.lab2_2 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.lab3_2 to javafx.fxml;
    exports com.example.lab3_2;
}