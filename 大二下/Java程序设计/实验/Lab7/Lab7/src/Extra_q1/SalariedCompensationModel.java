package Extra_q1;

public class SalariedCompensationModel implements CompensationModel {
    private double weeklySalary;

    public SalariedCompensationModel(double weeklySalary) {
        this.weeklySalary = weeklySalary;
    }

    @Override
    public double earnings() {
        return weeklySalary;
    }

    @Override
    public String toString() {
        return "SalariedCompensationModel{" +
                "weeklySalary=" + weeklySalary +
                '}';
    }
}
