package Extra_q2;

import java.util.ArrayList;

public class Test
{
    public static void main(String[] args)
    {
        //创建三个类中每一个类的对象，在ArrayList＜CarbonFootprint＞中放置对这些对象的引用，然后遍历ArrayList，以多态方式调用每个对象的getCarbonFootball方法。对于每个对象，打印一些识别信息和对象的碳足迹。
        Bicycle bicycle = new Bicycle("呆呆蓝", 800.0, 20.0);
        Building building = new Building("德旺图书馆", 1000.0, 150.0);
        Car car = new Car("奔驰", 900.0, 1000.0);

        ArrayList<CarbonFootprint> carbonFootprints = new ArrayList<>();

        carbonFootprints.add(bicycle);
        carbonFootprints.add(building);
        carbonFootprints.add(car);

        for(CarbonFootprint elem : carbonFootprints)
        {
            System.out.println(elem);
            System.out.println("Carbon footprint is " + elem.getCarbonFootprint() + "\n");
        }

    }
}
