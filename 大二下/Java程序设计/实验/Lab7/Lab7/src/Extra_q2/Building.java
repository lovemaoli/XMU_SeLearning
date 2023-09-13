package Extra_q2;

public class Building implements CarbonFootprint
{
    private double volume;
    private double height;
    private String name;

    public Building(String name, double volume, double height)
    {
        this.volume = volume;
        this.height = height;
        this.name = name;
    }

    public double getVolume() {
        return volume;
    }

    public void setVolume(double volume) {
        this.volume = volume;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
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
        return String.format("Building's name is %s.%nHeight is %.2f.%nVolume is %.2f.",
                getName(), getHeight(), getVolume());
    }

    @Override
    public double getCarbonFootprint()
    {
        return getVolume();
    }
}
