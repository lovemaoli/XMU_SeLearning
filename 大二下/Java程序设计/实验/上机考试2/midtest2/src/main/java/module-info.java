module com.example.midtest2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.example.midtest2 to javafx.fxml;
    exports com.example.midtest2;
}