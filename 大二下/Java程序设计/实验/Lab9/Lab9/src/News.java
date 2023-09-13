import java.util.Arrays;
import java.util.HashSet;

public class News {
    public static void main(String[] args) {
        String article="PITTSBURGH (AP) — Carnegie Mellon University will hire a researcher from the Library of Congress to help it decode a collection that includes two WWII German Enigma machines.The university wants to encourage the study of 19th and 20th century computers, calculators, encryption machines and other materials related to the history of computer science.“When we look back and we see this, we see who we remember,” Andrew Moore, dean of CMU’s School of Computer Science, said, adding his students are increasingly asking for courses about the history of the field. “We see people who took technology to save lives and save the world.”Pamela McCorduck, a prolific author on the history and future of artificial intelligence and the widow of Joseph Traub, a renowned computer scientist and the former head of CMU’s Computer Science Department, permanently loaned to the university a collection of early computers, books and letters. The collection, anchored by a three-rotor and four-rotor Enigma machine, is on display in the Fine and Rare Book Room in CMU’s Hunt Library in Oakland. The gift makes CMU one of a few institutions in the United States with Enigma machines. Even fewer display them.";
        String a = article.trim().replaceAll("\\pP", " ").toLowerCase();//去除标点符号
        String[] words=a.split(" ");//将字符串转换为数组
        HashSet<String> hashSet=new HashSet<>();//创建一个HashSet集合
        hashSet.addAll(Arrays.asList(words));//将数组转换为集合
        System.out.println(hashSet);//输出集合
        System.out.println("输出含the句子：");
        //利用正则表达式输出以下新闻片段中包含the的句子。
        //用正则表达式将字符串按照句号分割
        String[] sentences=article.split("\\.");
        //遍历数组
        for(String sentence:sentences)
        {
            if(sentence.matches(".*\\bthe\\b.*"))//判断句子中是否包含the
            {
                System.out.println(sentence+".");
            }
        }
    }
}
