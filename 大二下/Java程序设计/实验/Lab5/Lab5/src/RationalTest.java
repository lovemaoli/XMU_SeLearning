public class RationalTest
{
    public static void main(String[] args)
    {
        Rational test1 = new Rational(5, 6);
        Rational test2 = new Rational(15, 16);
        Rational test3 = new Rational(6, 9);
        Rational test4 = new Rational(6, 20);

        System.out.println("test1 is " + test1.toString());
        System.out.println("test2 is " + test2.toString());
        System.out.println("test3 is " + test3.toString());
        System.out.println("test4 is " + test4.toString());
        System.out.println("test1 is " + test1.print(4));
        System.out.println("test2 is " + test2.print(4));
        System.out.println("test3 is " + test3.print(4));
        System.out.println("test4 is " + test4.print(4));

        Rational addtest = test1.add(test2);
        System.out.println("test1 + test2 is " + addtest.toString());

        Rational subtest = test1.sub(test2);
        System.out.println("test1 - test2 is " + subtest.toString());

        Rational multest = test1.multiply(test2);
        System.out.println("test1 * test2 is " + multest.toString());

        Rational divtest = test1.divide(test2);
        System.out.println("test1 / test2 is " + divtest.toString());

    }
}
