/*
用于启动程序，加载主界面
 */
package com.maoli.notepad_maoli;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.fxml.JavaFXBuilderFactory;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class mainApplication extends Application {
    public static Map<String, Object> controllers = new HashMap<>();
    public static Map<String, Object> globals = new HashMap<>();

    GlobalClass global = new GlobalClass();

    @Override
    public void start(Stage primaryStage) throws Exception
    {
        globals.put("global", global);
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("Main.fxml"));
        fxmlLoader.setBuilderFactory(new JavaFXBuilderFactory());
        Parent root = fxmlLoader.load();
        primaryStage.setTitle("无标题 - 记事本");
        primaryStage.setScene(new Scene(root));
        primaryStage.getIcons().add(new Image("file:src/main/java/com/maoli/notepad_maoli/icon.png"));
        primaryStage.show();

        notepadController controller = fxmlLoader.getController();
        controller.mainStage(primaryStage);
        controller.zoominit();
        primaryStage.setOnCloseRequest(event -> {
            if (controller.getStatus() != 3)
            {
                if (controller.getCurrentPath() == null)
                {
                    Alert alert = new Alert(AlertType.CONFIRMATION);
                    alert.setTitle("记事本");
                    alert.setHeaderText("你想将更改保存到 无标题 吗？");
                    Optional<ButtonType> result = alert.showAndWait();

                    if (result.get() == ButtonType.OK)
                    {
                        if(controller.saveAs())
                            primaryStage.close();
                    }else if (result.get() == ButtonType.CANCEL)
                    {
                        primaryStage.close();
                    }
                }
                else
                {
                    Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
                    alert.setTitle("记事本");
                    alert.setHeaderText("你想将更改保存到 " + controller.getCurrentPath() + " 吗？");
                    Optional<ButtonType> result = alert.showAndWait();
                    if (result.get() == ButtonType.OK)
                    {
                        controller.save();
                        primaryStage.close();
                    }
                    else if (result.get() == ButtonType.CANCEL)
                    {
                        primaryStage.close();
                    }
                }
            }
            event.consume();
        });
    }

    public static void main(String[] args)
    {
        launch(args);
    }
}