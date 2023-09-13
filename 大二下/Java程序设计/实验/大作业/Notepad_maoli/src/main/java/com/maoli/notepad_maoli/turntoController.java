/*
用于跳转到指定行的控制器
 */
package com.maoli.notepad_maoli;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;

public class turntoController implements Initializable
{
    @FXML private TextField turntoTextField;
    public GlobalClass global;
    public notepadController controller;
    public int targetTurnto;

    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        global = (GlobalClass) mainApplication.globals.get("global");
        controller = (notepadController) mainApplication.controllers.get(notepadController.class.getSimpleName());
    }

    @FXML
    private void turntoConfirmButtonPressed()
    {
        targetTurnto = Integer.parseInt(turntoTextField.getText());
        global.turnto = targetTurnto;
        controller.turnto();
        controller.turntoClose();
    }

    @FXML
    private void turntoCancelButtonPressed()
    {
        controller.turntoClose();
    }
}
