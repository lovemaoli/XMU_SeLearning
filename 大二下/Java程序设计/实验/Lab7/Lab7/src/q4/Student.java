package q4;
/*
 定义Student类包含name和address属性，和setName、setAddress方法，
 当姓名长度小于1或者大于5时抛出IllegaNameException，
 当地址中不含有“省”或者“市”关键字时抛出IllegalAddressException。
 */
public class Student {
    private String name;
    private String address;

    public Student(String name, String address) {
        this.name = name;
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) throws IllegalNameException {
        if (name.length() < 1 || name.length() > 5) {
            throw new IllegalNameException("The length of name must be >=1 and <=5");
        }
        this.name = name;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) throws IllegalAddressException {
        if (!(address.contains("省") || address.contains("市"))) {
            throw new IllegalAddressException("Address must contain \"省\" or \"市\"");
        }
        this.address = address;
    }

    @Override
    public String toString() {
        return String.format("Name: %s%nAddress: %s%n", getName(), getAddress());
    }
}
