import java.util.*;

public class WordTypeCount {
    public static void main(String[] args) {
        // create HashMap to store String keys and Integer values
        Map<Character, Integer> myMap = new HashMap<>();

        createMap(myMap); // create map based on user input
        displayMap(myMap); // display map content
    }

    // create map from user input
    private static void createMap(Map<Character, Integer> map) {
        Scanner scanner = new Scanner(System.in); // create scanner
        System.out.println("Enter a string:"); // prompt for user input
        String tokens = scanner.nextLine();

        // tokenize the input
        tokens = tokens.toLowerCase().replaceAll(" ", "");// 转换为小写并去除空格
        tokens = tokens.replaceAll("\\pP", "");// 去除标点符号

        // processing input text
        char[] letter = tokens.toCharArray();
        for (char l : letter) {
            if (map.containsKey(l)) {
                int count = map.get(l);
                map.put(l, count + 1);
            } else {
                map.put(l, 1);
            }
        }
    }

    // display map content
    private static void displayMap(Map<Character, Integer> map) {
        Set<Character> keys = map.keySet(); // get keys

        // sort keys
        TreeSet<Character> sortedKeys = new TreeSet<>(keys);

        System.out.printf("%nMap contains:%nKey\t\tValue%n");

        // generate output for each key in map
        for (Character key : sortedKeys) {
            System.out.printf("%-5s%5s%n", key, map.get(key));
        }

        System.out.printf(
                "%nsize: %d%nisEmpty: %b%n", map.size(), map.isEmpty());
    }
}