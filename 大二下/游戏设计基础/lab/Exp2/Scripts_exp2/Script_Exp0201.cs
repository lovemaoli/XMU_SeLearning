using UnityEngine;
using UnityEditor;


public class Script_Exp0201
{
	//菜单排序

	[MenuItem("Root/Test1", false, 1)]
	static void Test1()
	{
	}

	[MenuItem("Root/Test0", false, 0)]
	static void Test0()
	{
	}

	[MenuItem("Root/Test/2")]
	static void Test2()
	{
	}

	[MenuItem("Root/Test/2", true, 20)]
	static bool Test2Validation()
	{
		//false表示Root/Test/2菜单将置灰不可点击
		return false;
	}

	[MenuItem("Root/Test3", false, 3)]
	static void Test3()
	{
		//勾选中框的菜单
		var menuPath = "Root/Test3";
		bool mchecked = Menu.GetChecked(menuPath);
		Menu.SetChecked(menuPath, !mchecked);
	}
}

