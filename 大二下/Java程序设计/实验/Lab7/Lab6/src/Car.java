

public class Car extends Vehicle {
    //小汽车类，有载客量（人）、车厢数（2厢或3厢）等属性
    private int passenger;
    private int carNum;
    //构造方法
    public Car(String brand, String color, int year, int passenger, int carNum) {
        super(brand, color, year);
        try{
            this.passenger = passenger;
            if (carNum != 2 && carNum != 3) {
                throw new Exception("车厢数只能为2或3");
            }
            //检查车厢数（2厢或3厢）
            this.carNum = carNum;
        }catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
    //getter和setter方法
    public int getPassenger() {
        return passenger;
    }
    public void setPassenger(int passenger) {
        this.passenger = passenger;
    }
    public int getCarNum() {
        return carNum;
    }
    public void setCarNum(int carNum) {
        try{
            if (carNum != 2 && carNum != 3) {
                throw new Exception("车厢数只能为2或3");
            }
            //检查车厢数（2厢或3厢）
            this.carNum = carNum;
        }catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
    //重写抽象方法，列出汽车的基本信息
    @Override
    public void showInfo() {
        System.out.println("小汽车，品牌：" + super.getBrand() + " 颜色：" + super.getColor() + " 出厂年份：" + super.getYear() + " 载客量：" + passenger + " 车厢数：" + carNum);
    }

}
