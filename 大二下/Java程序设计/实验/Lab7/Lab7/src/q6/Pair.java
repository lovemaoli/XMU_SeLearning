package q6;

public class Pair<F, S> {
    private F a;
    private S b;

    public F geta() {
        return a;
    }

    public S getb() {
        return b;
    }

    public void seta(F a) {
        this.a = a;
    }

    public void setb(S b) {
        this.b = b;
    }

    public static void main(String[] args) {
        Pair<String,Integer> pair = new Pair<String,Integer>();
        pair.seta("maoli");
        pair.setb(5201314);
        System.out.println("Pair1:<" + pair.geta() + "," + pair.getb() + ">");
    }
}
