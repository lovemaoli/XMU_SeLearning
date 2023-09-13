package Extra_q1;

public class HourlyCompensationModel implements CompensationModel {
    private double wage;
    private double hours;

    public HourlyCompensationModel(double wage, double hours) {
        this.wage = wage;
        this.hours = hours;
    }

    @Override
    public double earnings() {
        if (hours <= 40) {
            return wage * hours;
        } else {
            return 40 * wage + (hours - 40) * wage * 1.5;
        }
    }

    @Override
    public String toString() {
        return "HourlyCompensationModel{" +
                "wage=" + wage +
                ", hours=" + hours +
                '}';
    }
}
