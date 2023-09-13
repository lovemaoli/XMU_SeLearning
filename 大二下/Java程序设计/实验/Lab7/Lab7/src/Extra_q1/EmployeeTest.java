package Extra_q1;

public class EmployeeTest {
    public static void main(String[] args) {
        //创建四个 Employee 对象
        System.out.println("初始化员工信息:");
        Employee[] employees = new Employee[4];
        employees[0] = new Employee("John", "Smith", "111-11-1111", new SalariedCompensationModel(800));
        employees[1] = new Employee("Lisa", "Barnes", "888-88-8888", new CommissionCompensationModel(10000, 0.06));
        employees[2] = new Employee("Mark", "Jones", "777-77-7777", new BasePlusCommissionCompensationModel(5000, 0.04, 300));
        employees[3] = new Employee("John", "Doe", "666-66-6666", new SalariedCompensationModel(1000));

        for (Employee employee : employees) {
            System.out.println(employee);
            //输出earning
            System.out.printf("Earning: $%,.2f%n%n", employee.compensationModel.earnings());
        }
        //动态地改变员工的 CompensationModel，重新显示他的收入
        employees[0].setCompensationModel(new CommissionCompensationModel(10000, 0.1));
        employees[1].setCompensationModel(new BasePlusCommissionCompensationModel(5000, 0.05, 300));
        employees[2].setCompensationModel(new SalariedCompensationModel(1200));
        employees[3].setCompensationModel(new CommissionCompensationModel(20000, 0.15));

        System.out.println("动态改变员工的 CompensationModel，重新显示他的收入:");
        for (Employee employee : employees) {
            System.out.println(employee);
            //输出earning
            System.out.printf("Earning: $%,.2f%n%n", employee.compensationModel.earnings());
        }
    }
}
