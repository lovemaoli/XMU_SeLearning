/*
用于存储全局变量，以便在各个类中调用
 */
package com.maoli.notepad_maoli;

import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
public class GlobalClass {
    //查找
    public String search;
    //查找时是否忽略大小写
    public boolean isCaseIgnored;
    //替换
    public String replace;
    //转到
    public int turnto;
    //字体
    public Font font;
    //字体颜色
    public String fontColor;
    //字体
    public String fontFamily;
    //字形
    public FontWeight fontWeight;
    public FontPosture fontPosture;
    //大小
    public double size;
}
