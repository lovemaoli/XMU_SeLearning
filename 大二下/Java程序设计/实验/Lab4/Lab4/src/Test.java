// 交通信号灯枚举类
enum TrafficLight {
    RED(255, 0, 0), // 红灯
    YELLOW(255, 255, 0), // 黄灯
    GREEN(0, 255, 0); // 绿灯

    private int r, g, b;

    TrafficLight(int r, int g, int b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }

    public int getR() {
        return r;
    }

    public int getG() {
        return g;
    }

    public int getB() {
        return b;
    }
}

// 测试类
public class Test {
    public static void main(String[] args) {
        System.out.println("红灯 RGB 值：" + TrafficLight.RED.getR() + "," + TrafficLight.RED.getG() + "," + TrafficLight.RED.getB());
        System.out.println("黄灯 RGB 值：" + TrafficLight.YELLOW.getR() + "," + TrafficLight.YELLOW.getG() + "," + TrafficLight.YELLOW.getB());
        System.out.println("绿灯 RGB 值：" + TrafficLight.GREEN.getR() + "," + TrafficLight.GREEN.getG() + "," + TrafficLight.GREEN.getB());
    }
}
