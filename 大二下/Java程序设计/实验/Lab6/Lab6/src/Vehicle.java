public abstract class Vehicle {
    //车辆抽象类，有商标、颜色、出厂年等属性
    private String brand;
    private String color;
    private int year;
    //构造方法
    public Vehicle(String brand, String color, int year) {
        this.brand = brand;
        this.color = color;
        this.year = year;
    }
    //getter和setter方法
    public String getBrand() {
        return brand;
    }
    public void setBrand(String brand) {
        this.brand = brand;
    }
    public String getColor() {
        return color;
    }
    public void setColor(String color) {
        this.color = color;
    }
    public int getYear() {
        return year;
    }
    public void setYear(int year) {
        this.year = year;
    }
    //抽象方法，列出车辆的基本信息
    public abstract void showInfo();
}