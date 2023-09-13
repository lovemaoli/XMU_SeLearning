// 交通工具类Vehicle
class Vehicle {
    public void run() {
        System.out.println("这是交通工具run方法");
    }
}

// Motor类，表示汽车
class Motor extends Vehicle {
    @Override
    public void run() {
        System.out.println("这是汽车run方法");
    }
}

// Ship类，表示船
class Ship extends Vehicle {
    @Override
    public void run() {
        System.out.println("这是船run方法");
    }
}

// Aeroplane类，表示飞机
class Aeroplane extends Vehicle {
    @Override
    public void run() {
        System.out.println("这是飞机run方法");
    }
}

// Bus类，表示公共汽车
class Bus extends Motor {
    @Override
    public void run() {
        System.out.println("这是公共汽车run方法");
    }
}

// Car类，表示轿车
class Car extends Motor {
    @Override
    public void run() {
        System.out.println("这是轿车run方法");
    }
}

// 测试类Test
public class Test {
    public static void main(String[] args) {
        Vehicle vehicle = new Vehicle();
        vehicle.run();

        vehicle = new Motor();
        vehicle.run();

        vehicle = new Ship();
        vehicle.run();

        vehicle = new Aeroplane();
        vehicle.run();

        vehicle = new Bus();
        vehicle.run();

        vehicle = new Car();
        vehicle.run();
    }
}
