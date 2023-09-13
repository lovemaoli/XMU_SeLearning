package Extra_q2;

public class Car implements CarbonFootprint
{
    private double fuelConsumption;
    private double distance;
    private String name;

    public Car(String name, double fuelConsumption, double distance)
    {
        this.fuelConsumption = fuelConsumption;
        this.distance = distance;
        this.name = name;
    }

    public double getFuelConsumption() {
        return fuelConsumption;
    }

    public void setFuelConsumption(double fuelConsumption) {
        this.fuelConsumption = fuelConsumption;
    }

    public double getDistance() {
        return distance;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString()
    {
        return String.format("Car's name is %s.%nFuel consumption is %.2f.%nDistance is %.2f.",
                getName(), getFuelConsumption(), getDistance());
    }

    @Override
    public double getCarbonFootprint()
    {
        return getFuelConsumption() * getDistance();
    }
}