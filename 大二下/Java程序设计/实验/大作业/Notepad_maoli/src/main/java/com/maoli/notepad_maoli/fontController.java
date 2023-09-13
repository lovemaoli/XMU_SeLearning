/*
用于字体选择的控制器，包括字体、字形、大小、颜色
 */
package com.maoli.notepad_maoli;

import java.awt.GraphicsEnvironment;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;

public class fontController implements Initializable {
    public GlobalClass global;
    public notepadController controller;
    @FXML private ListView<String> fontSelector;
    @FXML private ListView<String> glyphSelector;
    @FXML private ListView<String> sizeSelector;
    @FXML private ComboBox<String> fontColorSelector;
    @FXML private TextField fontTextField;
    @FXML private TextField glyphTextField;
    @FXML private TextField sizeTextField;
    @FXML private TextArea fontShowTextArea;
    private static final String ChineseShowText = "测试文本";
    private static final String EnglishShowText = "XMU Notepad";
    private static final String NumberShowText = "1234567890";

    //字体
    private Font font;

    //所有大小
    private ObservableList<String> sizeArray;
    private final int[] sizeIntArray = {8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72, 42, 36, 26, 24, 22, 18, 16, 15, 14, 12, 10, 9, 8, 7, 6, 5};

    @Override
    public void initialize(URL location, ResourceBundle resources)
    {

        global = (GlobalClass) mainApplication.globals.get("global");
        controller = (notepadController) mainApplication.controllers.get(notepadController.class.getSimpleName());

        GraphicsEnvironment e = GraphicsEnvironment.getLocalGraphicsEnvironment();
        //存储所有字体
        ObservableList<String> fontArray = FXCollections.observableArrayList(e.getAvailableFontFamilyNames());
        //所有字形
        ObservableList<String> glyphArray = FXCollections.observableArrayList("常规", "粗体", "斜体");
        sizeArray = FXCollections.observableArrayList("8", "9", "10", "11", "12", "14", "16", "18", "20",
                "22", "24", "26", "28", "36", "48", "72", "初号", "小初", "一号", "小一", "二号", "小二", "三号", "小三",
                "四号", "小四", "五号", "小五", "六号", "小六", "七号", "八号");

        ObservableList<String> colorArray = FXCollections.observableArrayList("BLACK", "BLUE", "GREEN", "GRAY", "RED", "WHITE", "YELLOW");

        fontSelector.setItems(fontArray);
        glyphSelector.setItems(glyphArray);
        sizeSelector.setItems(sizeArray);
        fontColorSelector.setItems(colorArray);

        fontTextField.textProperty().bind(fontSelector.getSelectionModel().selectedItemProperty());
        glyphTextField.textProperty().bind(glyphSelector.getSelectionModel().selectedItemProperty());
        sizeTextField.textProperty().bind(sizeSelector.getSelectionModel().selectedItemProperty());

        fontSelector.getSelectionModel().select("微软雅黑");
        glyphSelector.getSelectionModel().select(0);
        sizeSelector.getSelectionModel().select(4);
        fontColorSelector.getSelectionModel().select(0);

        myFontSet();

        //监听函数
        fontSelector.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> myFontSet());

        glyphSelector.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> myFontSet());

        sizeSelector.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> myFontSet());

        fontColorSelector.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> myFontSet());
    }


    //字体设置已知bug：部分字体无法切换常规与粗体（推荐用微软雅黑进行测试）；斜体无法正常显示
    private void myFontSet()
    {
        //默认五号
        double fontSize = 20;
        for(int i = 0; i < sizeIntArray.length; i++)
        {
            if(sizeSelector.getSelectionModel().getSelectedItem().equals(sizeArray.get(i)))
            {
                fontSize = Double.parseDouble(String.valueOf(sizeIntArray[i]));
                break;
            }
        }

        if(glyphSelector.getSelectionModel().getSelectedItem().equals("常规"))
        {
            font = Font.font(fontSelector.getSelectionModel().getSelectedItem(), FontWeight.NORMAL, FontPosture.REGULAR, fontSize);
            global.fontWeight = FontWeight.NORMAL;
            global.fontPosture = FontPosture.REGULAR;
        }
        else if(glyphSelector.getSelectionModel().getSelectedItem().equals("粗体"))
        {
            font = Font.font(fontSelector.getSelectionModel().getSelectedItem(), FontWeight.BOLD, FontPosture.REGULAR, fontSize);
            global.fontWeight = FontWeight.BOLD;
            global.fontPosture = FontPosture.REGULAR;
        }
        else if(glyphSelector.getSelectionModel().getSelectedItem().equals("斜体"))
        {
            font = Font.font(fontSelector.getSelectionModel().getSelectedItem(), FontWeight.NORMAL, FontPosture.ITALIC, fontSize);
            global.fontWeight = FontWeight.NORMAL;
            global.fontPosture = FontPosture.ITALIC;
        }
        //字体颜色
        String fontColor = fontColorSelector.getSelectionModel().getSelectedItem();
        global.font = font;
        global.fontColor = fontColor;
        global.fontFamily = fontSelector.getSelectionModel().getSelectedItem();
        global.size = fontSize;
        fontShowTextArea.setFont(font);
        fontShowTextArea.setStyle("-fx-text-fill:" + fontColor);
        fontShowTextArea.setText(ChineseShowText + "\n" + EnglishShowText + "\n" + NumberShowText);
    }

    @FXML
    private void fontInterfaceCancelButtonPressed()
    {
        controller.fontChooserClose();
    }

    @FXML
    private void fontInterfaceConfirmButtonPressed()
    {
        controller.fontChooserConfirm();
        controller.fontChooserClose();
    }
}
