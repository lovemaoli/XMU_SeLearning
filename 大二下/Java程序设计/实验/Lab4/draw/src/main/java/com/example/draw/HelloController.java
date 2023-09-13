package com.example.draw;

import java.security.SecureRandom;
import java.util.Scanner;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Ellipse;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
public class HelloController {
    @FXML private Pane drawingAreaPane;
    @FXML private Label countLabel;
    @FXML private Button drawButton;
    @FXML private Button undoButton;
    @FXML private Button clearButton;
    private final SecureRandom random = new SecureRandom();
    private final Scanner scanner = new Scanner(System.in);
    private Integer count = 0;

    @FXML
    private void drawClicked(ActionEvent event) {
        if (count >= 20) {
            drawButton.setDisable(true);
            return;
        }
        Integer choice = random.nextInt(3);
        switch (choice) {
            case 0 -> {
                System.out.println("绘画直线：");
                System.out.println("请输入开始点：");
                Double startX = 0.0;
                Double startY = 0.0;
                startX = scanner.nextDouble();
                startY = scanner.nextDouble();
                System.out.println("请输入结束点：");
                Double endX = 0.0;
                Double endY = 0.0;
                endX = scanner.nextDouble();
                endY = scanner.nextDouble();
                System.out.println("生成成功！");
                Line line = new Line();
                line.setStartX(startX);
                line.setStartY(startY);
                line.setEndX(endX);
                line.setEndY(endY);
                drawingAreaPane.getChildren().add(line);
                count++;
            }
            case 1 -> {
                System.out.println("绘画矩形：");
                System.out.println("请输入左上角坐标：");
                Double topLeftX = 0.0;
                Double topLeftY = 0.0;
                topLeftX = scanner.nextDouble();
                topLeftY = scanner.nextDouble();
                System.out.println("请输入右下角坐标：");
                Double bottomRightX = 0.0;
                Double bottomRightY = 0.0;
                bottomRightX = scanner.nextDouble();
                bottomRightY = scanner.nextDouble();
                System.out.println("生成成功！");
                Rectangle rectangle = new Rectangle(topLeftX, topLeftY,
                        Math.abs(topLeftX - bottomRightX),
                        Math.abs(topLeftY - bottomRightY));
                rectangle.setStroke(Color.BLACK);
                rectangle.setFill(Color.TRANSPARENT);
                drawingAreaPane.getChildren().add(rectangle);
                count++;
            }
            case 2 -> {
                System.out.println("绘画椭圆：");
                System.out.println("请输入中心坐标：");
                Double centerX = 0.0;
                Double centerY = 0.0;
                centerX = scanner.nextDouble();
                centerY = scanner.nextDouble();
                System.out.println("请输入长短轴长度：");
                Double radiusX = 0.0;
                Double radiusY = 0.0;
                radiusX = scanner.nextDouble();
                radiusY = scanner.nextDouble();
                System.out.println("生成成功！");
                Ellipse ellipse = new Ellipse(centerX, centerY, radiusX, radiusY);
                ellipse.setStroke(Color.BLACK);
                ellipse.setFill(Color.TRANSPARENT);
                drawingAreaPane.getChildren().add(ellipse);
                count++;
            }
        }
        countLabel.setText(count +"/20");
    }

    @FXML
    private void undoClicked() {
        if (count > 0) {
            drawingAreaPane.getChildren().remove(count - 1);
            count--;
            countLabel.setText(count +"/20");
        }
    }

    @FXML
    private void clearClicked() {
        drawingAreaPane.getChildren().clear();
        count = 0;
        countLabel.setText(count +"/20");
    }
}