
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);
    private static final ArrayList<Vehicle> vehicles = new ArrayList<>();

    public static void main(String[] args) {
        boolean exit = false;
        do {
            try{
                System.out.println("请输入对应输入进行相应菜单操作：");
                System.out.println("1.    新增车辆");
                System.out.println("2.    查询车辆");
                System.out.println("3.    列出所有车辆");
                System.out.println("4.    结束程序");
                int choice = scanner.nextInt();
                if(choice<1 || choice>4){
                    throw new Exception();
                }
                switch (choice) {
                    case 1 -> {
                        do {
                            try {
                                System.out.println("请输入车辆信息，示例：");
                                System.out.println("小汽车 丰田 红色 4 2007 2厢");
                                System.out.println("卡车 雷诺 红色 3.5 2008");
                                String info = scanner.nextLine();
                                if (info.equals("")) {
                                    info = scanner.nextLine();
                                }
                                String[] infos = info.split(" ");
                                //若用户输入end则结束新增，重新显示主菜单
                                if (infos[0].equals("end")) {
                                    break;
                                }
                                //检查用户输入的车辆信息是否符合要求
                                if (infos.length == 6) {
                                    if (!infos[0].equals("小汽车")) {
                                        System.out.println("第一个参数必须为小汽车或者卡车");
                                        throw new Exception();
                                    }
                                    if (!infos[5].equals("2厢") && !infos[5].equals("3厢")) {
                                        throw new Exception();
                                    }
                                    if (infos[5].equals("2厢")) {
                                        infos[5] = "2";
                                    }
                                    if (infos[5].equals("3厢")) {
                                        infos[5] = "3";
                                    }
                                    Car car = new Car(infos[1], infos[2], Integer.parseInt(infos[4]), Integer.parseInt(infos[3]), Integer.parseInt(infos[5]));
                                    vehicles.add(car);
                                } else if (infos.length == 5) {
                                    if (!infos[0].equals("卡车")) {
                                        System.out.println("第一个参数必须为小汽车或者卡车");
                                        throw new Exception();
                                    }
                                    Trunk trunk = new Trunk(infos[1], infos[2], Integer.parseInt(infos[4]), Double.parseDouble(infos[3]));
                                    vehicles.add(trunk);
                                } else {
                                    throw new Exception();
                                }
                                System.out.println("创建成功");
                                vehicles.get(vehicles.size() - 1).showInfo();//显示创建的车辆信息
                                System.out.println();
                            }//创建对象初始值不合法
                            catch (IllegalArgumentException e) {
                                System.out.println("创建不成功");
                            }//创建对象时输入的参数个数不合法
                            catch (InputMismatchException e) {
                                System.out.println("创建不成功");
                            }//创建对象时输入的参数不合法
                            catch (Exception e) {
                                System.out.println("创建不成功");
                            }
                        } while (true);
                    }
                    case 2 -> {
                        do {
                            try {
                                System.out.println("请按照”类型 商标 颜色 出厂年“的顺序输入条件，若条件为空用“null”代替，2个示例：");
                                System.out.println("小汽车 丰田 红色 2007");
                                System.out.println("null 丰田 null null");
                                System.out.println("输入end返回上级菜单");
                                String info = scanner.nextLine();
                                if (info.equals("")) {
                                    info = scanner.nextLine();
                                }
                                if (info.equals("end")) {
                                    break;
                                }
                                String[] infos = info.split(" ");
                                if (infos.length != 4) {
                                    throw new Exception();
                                }
                                int result = 0;//记录符合条件的车辆数量
                                if(infos[0].equals("小汽车")){
                                    infos[0] = "Car";
                                }
                                if(infos[0].equals("卡车")){
                                    infos[0] = "Trunk";
                                }
                                for (Vehicle vehicle : vehicles) {
                                    if ((infos[0].equals("null") || infos[0].equals(vehicle.getClass().getSimpleName())) && (infos[1].equals("null") || infos[1].equals(vehicle.getBrand())) && (infos[2].equals("null") || infos[2].equals(vehicle.getColor())) && (infos[3].equals("null") || infos[3].equals(String.valueOf(vehicle.getYear())))) {
                                        result++;
                                    }
                                }
                                if (result == 0) {
                                    throw new Exception();
                                }
                                System.out.println("搜索到" + result + "辆车符合条件，信息如下：");
                                for (Vehicle vehicle : vehicles) {
                                    if ((infos[0].equals("null") || infos[0].equals(vehicle.getClass().getSimpleName())) && (infos[1].equals("null") || infos[1].equals(vehicle.getBrand())) && (infos[2].equals("null") || infos[2].equals(vehicle.getColor())) && (infos[3].equals("null") || infos[3].equals(String.valueOf(vehicle.getYear())))) {
                                        vehicle.showInfo();//显示符合条件的车辆信息
                                    }
                                }
                            } catch (Exception e) {
                                System.out.println("没有符合条件的车辆");
                            }
                        } while (true);
                    }
                    case 3 -> {
                        System.out.println("目前有" + vehicles.size() + "辆车信息如下：");
                        for (Vehicle vehicle : vehicles) {
                            vehicle.showInfo();//利用多态，显示所有车辆信息
                        }
                    }
                    case 4 -> exit = true;
                }

            }//处理类初始化错误的异常
            catch (ExceptionInInitializerError e){
                System.out.println("程序出现错误");
                exit = true;
            }//处理数据类型不匹配的异常
            catch (InputMismatchException e){
                System.out.println("请输入1-4的整数");
                scanner.nextLine();
            }//处理数组越界的异常
            catch (ArrayIndexOutOfBoundsException e){
                System.out.println("请输入1-4的整数");
                scanner.nextLine();
            }//处理除数为0的异常
            catch (ArithmeticException e){
                System.out.println("请输入1-4的整数");
                scanner.nextLine();
            }//处理空指针的异常
            catch (NullPointerException e){
                System.out.println("请输入1-4的整数");
                scanner.nextLine();
            }//处理其他异常
            catch(Exception e){
                System.out.println("请输入1-4的整数");
                scanner.nextLine();
            }
        }while(!exit);
    }
}