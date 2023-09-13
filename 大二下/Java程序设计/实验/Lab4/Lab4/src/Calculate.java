import java.util.Scanner;

// 基础图形类
class Graph {
    protected double area;

    public double getArea() {
        return area;
    }
}

// 三角形类
class Triangle extends Graph {
    private double a, b, c;

    public Triangle(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
        double p = (a + b + c) / 2;
        area = Math.sqrt(p * (p - a) * (p - b) * (p - c));
    }
}

// 矩形类
class Rectangle extends Graph {
    private double width, height;

    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
        area = width * height;
    }
}

public class Calculate {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < n; i++) {
            String line = scanner.nextLine();
            String[] params = line.split(" ");
            Graph graph;
            if (params.length == 2) {
                double a = Double.parseDouble(params[0]);
                double b = Double.parseDouble(params[1]);
                graph = new Rectangle(a, b);
            } else {
                double a = Double.parseDouble(params[0]);
                double b = Double.parseDouble(params[1]);
                double c = Double.parseDouble(params[2]);
                graph = new Triangle(a, b, c);
            }
            System.out.println(String.format("%.0f", graph.getArea()));
        }
    }
}
