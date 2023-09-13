package com.example.lab3_2;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.util.Random;

public class CanvasCircles extends Application {

    private final int CIRCLE_COUNT = 10;

    @Override
    public void start(Stage stage) {

        // 创建一个Canvas对象
        Canvas canvas = new Canvas(600, 400);

        // 获取GraphicsContext对象
        GraphicsContext gc = canvas.getGraphicsContext2D();

        // 创建一个Pane对象，将Canvas对象添加到Pane中
        Pane pane = new Pane(canvas);

        // 创建Scene对象，并将Pane对象设置为根节点
        Scene scene = new Scene(pane, 600, 400);

        // 设置窗口标题
        stage.setTitle("Canvas Circles");

        // 将Scene对象设置到Stage中
        stage.setScene(scene);

        // 生成随机数
        Random random = new Random();

        // 随机生成10个圆
        for (int i = 0; i < CIRCLE_COUNT; i++) {
            // 随机生成圆心坐标和半径大小
            double x = random.nextDouble() * canvas.getWidth();
            double y = random.nextDouble() * canvas.getHeight();
            double radius = random.nextDouble() * 50 + 10;

            // 随机生成颜色
            Color color = Color.rgb(random.nextInt(256), random.nextInt(256), random.nextInt(256));

            // 在Canvas上绘制圆
            gc.setFill(color);
            gc.fillOval(x - radius, y - radius, radius * 2, radius * 2);
        }

        // 显示窗口
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
