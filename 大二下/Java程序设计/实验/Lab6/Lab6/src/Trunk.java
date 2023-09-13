public class Trunk extends Vehicle {
    //卡车类，有载重量（吨）属性
    private double weight;
    //构造方法
    public Trunk(String brand, String color, int year, double weight) {
        super(brand, color, year);
        this.weight = weight;
    }
    //getter和setter方法
    public double getWeight() {
        return weight;
    }
    public void setWeight(int weight) {
        this.weight = weight;
    }
    //重写抽象方法，列出卡车的基本信息
    @Override
    public void showInfo() {
        System.out.println("卡车，品牌：" + super.getBrand() + " 颜色：" + super.getColor() + " 出厂年份：" + super.getYear() + " 载重量：" + weight + "吨");
    }
}
