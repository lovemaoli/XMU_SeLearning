public class Rational implements Comparable<Object>
{
    /*
     Rational 类表示有理数，并实现了分数加减乘除以及分数的大小比较。
     分子和分母都是 long 类型。
     */
    private long numerator; // 分子
    private long denominator; // 分母

    public long getNumerator()
    {
        return numerator;
    }

    public void setNumerator(long numerator)
    {
        this.numerator = numerator;
    }

    public long getDenominator()
    {
        return denominator;
    }

    public void setDenominator(long denominator)
    {
        this.denominator = denominator;
    }

    private static long gcd(long num1, long num2)
    {
        long result = 0;
        while(num2 != 0)
        {
            result = num1 % num2;
            num1 = num2;
            num2 = result;
        }
        return num1;
    }

    public Rational(long numerator, long denominator)
    {
        long gcd = gcd(numerator, denominator); // 对分数进行约分
        this.numerator = numerator / gcd;
        this.denominator = denominator / gcd;
    }

    public Rational()
    {
        this(0,1);
    } // 创建一个默认值为 0 的 Rational 对象

    public Rational add(Rational secondRational) {
        long lcd = (Math.abs(this.denominator * secondRational.getDenominator())) / gcd(this.denominator, secondRational.getDenominator());

        long num1 = (lcd / this.denominator) * this.numerator;
        long num2 = (lcd / secondRational.getDenominator()) * secondRational.getNumerator();

        return new Rational(num1 + num2, lcd);
    }

    public Rational sub(Rational secondRational)
    {
        long lcd = (Math.abs(this.getDenominator() * secondRational.getDenominator())) / gcd(this.getDenominator(), secondRational.getDenominator());

        long num1 = (lcd / this.getDenominator()) * this.getNumerator();
        long num2 = (lcd / secondRational.getDenominator()) * secondRational.getNumerator();

        return new Rational(num1 - num2, lcd);
    }

    public Rational multiply(Rational secondRational)
    {
        return new Rational(this.getNumerator() * secondRational.getNumerator(), this.getDenominator() * secondRational.getDenominator());
    }

    public Rational divide(Rational secondRational)
    {
        return new Rational(this.getNumerator() * secondRational.getDenominator(), this.getDenominator() * secondRational.getNumerator());
    }

    public String toString()
    {
        return String.format("%d/%d", numerator, denominator);
    }

    public String print(long precision)
    {
        double num = (double)numerator / denominator;
        return String.format("%." + precision + "f", num);
    }

    public int compareTo(Object o)
    {
        Rational num = (Rational)o;
        if((double)this.getNumerator()/this.getDenominator() > (double)num.getNumerator() / num.getDenominator())
            return 1;
        else if((double)this.getNumerator()/this.getDenominator() == (double)num.getNumerator() / num.getDenominator())
            return 0;
        else
            return -1;
    }

}
