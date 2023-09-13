package lab6;

//基础载具类
public class vehicle 
{
	
	private String carName;	//载具名称
	private String brand;	//车辆品牌
	private String color;	//车辆颜色
	private double capacity;	//小汽车载客量或卡车载重量
	private int year;		//出厂年份
	
	public String getCarName() {
		return carName;
	}

	public void setCarName(String carName) {
		this.carName = carName;
	}

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

	public double getCapacity() {
		return capacity;
	}

	public void setCapacity(double capacity) {
		this.capacity = capacity;
	}

	public int getYear() {
		return year;
	}

	public void setYear(int year) throws IllegalYearException 
	{
		if(year <= 0 || year > 9999)
			throw new IllegalYearException("Year must be > 0 and <= 9999");
		this.year = year;
	}
	
	//显示载具信息
//	public void printInfo()
//	{
//		//一开始用的printf，一直报错，所以改成println
////		System.out.printf("%s，品牌：%s 颜色：%s 出厂年份：%d 载客量：%f\n",
////						   carName, brand, color, year, capacity);
//		System.out.println(carName + "，品牌：" + brand + " 颜色：" + color + " 出厂年份：" + year + " 载客量：" + capacity);
//	};
//	
	@Override
	public String toString()
	{
		return String.format("%s，品牌：%s 颜色：%s 出厂年份：%d", getCarName(), getBrand(), getColor(), getYear());
	}
}
