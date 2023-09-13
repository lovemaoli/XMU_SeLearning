/*
    @Author:Huang Xu
    @ID:22920212204392
    @Date:2023/6/6
*/
package com.example.midtest2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class txtApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(txtApplication.class.getResource("txt-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Vowel Statistics");//设置窗口标题
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}