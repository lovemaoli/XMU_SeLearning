/*
    @Author:Huang Xu
    @ID:22920212204392
    @Date:2023/6/6
*/
package com.example.midtest2;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import java.io.File;
import javax.swing.*;
import java.io.FileNotFoundException;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.Scanner;

public class txtController {
    @FXML
    private TextArea infoArea;
    @FXML
    public void openFile() throws FileNotFoundException {
        //弹出打开目录的对话框，供用户选择要统计的txt文件所在的文件夹；
        JFileChooser jfc = new JFileChooser();
        jfc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY); //只能选择目录
        int result = jfc.showOpenDialog(null); //弹出对话框
        File file = null;
        if (result == JFileChooser.APPROVE_OPTION) { //点击了“确定”
            file = jfc.getSelectedFile(); //获取目录路径
            System.out.println(file.getAbsolutePath()); //输出绝对路径,用于测试
        }
        //查找文件夹下的所有txt文件，并统计每个txt文件中的每个英文字符数；
        File[] files = file.listFiles(); //获取文件夹下的所有文件
        int[] count = new int[26]; //用于统计每个英文字符数
        for (File f : files) { //遍历文件夹下的所有文件
            if (f.getName().endsWith(".txt")) { //判断是否为txt文件
                //将文件路径+文件名的txt目录输出在textArea
                infoArea.appendText(f.getAbsolutePath() + "\n");
                String content = new Scanner(f).useDelimiter("\\Z").next();
                //统计每个txt文件中的每个英文字符数
                for (int i = 0; i < content.length(); i++) {
                    char c = content.charAt(i);
                    if (c >= 'a' && c <= 'z') {
                        count[c - 'a']++;
                    } else if (c >= 'A' && c <= 'Z') {
                        count[c - 'A']++;
                    }
                }
            }
        }
        //检查是否有出现，如果有则将每个英文字符数输出在textArea
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) {
                char c = (char) ('a' + i);
                infoArea.appendText(c + " 字母出现，总个数：" + count[i] + "\n");
            }
        }
        //将结果写入“结果.txt”,放在类的同级目录下
        File resultFile = new File(txtController.class.getResource("").getPath() + "结果.txt");
        try {
            resultFile.createNewFile();
        } catch (Exception e) {
            e.printStackTrace();
        }
        //将textArea的内容保存在文件
        String resultString = infoArea.getText();
        try {
            java.io.FileWriter fw = new java.io.FileWriter(resultFile);
            fw.write(resultString);
            fw.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        //打开文件
        try {
            java.awt.Desktop.getDesktop().open(resultFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
        //弹出对话框，提示用户统计完成；
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("提示");
        alert.setHeaderText("统计完成");
        alert.setContentText("统计完成");
        alert.showAndWait();
    }
}