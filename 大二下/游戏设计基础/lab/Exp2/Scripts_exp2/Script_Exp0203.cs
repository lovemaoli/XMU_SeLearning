using UnityEngine;
using UnityEditor;

public class Script_Exp0203
{
	[MenuItem("Assets/Create/My Create/Cube", false, 2)]
	static void CreateCube()
	{
		GameObject.CreatePrimitive(PrimitiveType.Cube); //创建立方体
	}

	[MenuItem("Assets/Create/My Create/Sphere", false, 1)]
	static void CreateSphere()
	{
		GameObject.CreatePrimitive(PrimitiveType.Sphere);//创建球体
	}
}
