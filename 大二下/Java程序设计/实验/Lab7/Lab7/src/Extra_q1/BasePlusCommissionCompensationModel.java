package Extra_q1;

public class BasePlusCommissionCompensationModel implements CompensationModel {
    private double grossSales;
    private double commissionRate;
    private double baseSalary;

    public BasePlusCommissionCompensationModel(double grossSales, double commissionRate, double baseSalary) {
        this.grossSales = grossSales;
        this.commissionRate = commissionRate;
        this.baseSalary = baseSalary;
    }

    @Override
    public double earnings() {
        return grossSales * commissionRate + baseSalary;
    }

    @Override
    public String toString() {
        return "BasePlusCommissionCompensationModel{" +
                "grossSales=" + grossSales +
                ", commissionRate=" + commissionRate +
                ", baseSalary=" + baseSalary +
                '}';
    }
}
