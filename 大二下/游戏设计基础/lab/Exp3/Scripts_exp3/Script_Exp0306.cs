using UnityEngine;
using UnityEngine.UI;

public class Script_Exp0306 : MonoBehaviour {
    public InputField inputField;
    public Text tips;
	void Start () {
        //监听输入后事件
        inputField.onValueChanged.AddListener((string content) => {
            tips.text = string.Format("已经输入{0}个字符", content.Length);
        });

        //监听输入文字变化，当出现a时替换成*号
        inputField.onValidateInput += delegate (string input, int charIndex, char addedChar) 
        {
            if(addedChar == 'a'){
                addedChar = '*';
            }
            return addedChar;
        };
	}
}
