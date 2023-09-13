module com.maoli.notepad_maoli {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.maoli.notepad_maoli to javafx.fxml;
    exports com.maoli.notepad_maoli;
}