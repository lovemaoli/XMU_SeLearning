using UnityEngine;
using UnityEditor;

public class Script_Exp0204
{
	[InitializeOnLoadMethod]
	static void InitializeOnLoadMethod()
	{
		EditorApplication.projectWindowItemOnGUI = delegate (string guid, Rect selectionRect) {
			//在Project视图中选择一个资源

			if (Selection.activeObject &&
				guid == AssetDatabase.AssetPathToGUID(AssetDatabase.GetAssetPath(Selection.activeObject)))
			{

				//设置拓展按钮区域
				float width = 50f;
				selectionRect.x += (selectionRect.width - width);
				selectionRect.y += 2f;
				selectionRect.width = width;
				GUI.color = Color.red;

				//点击事件
				if (GUI.Button(selectionRect, "click"))
				{
					Debug.LogFormat("click : {0}", Selection.activeObject.name);
				}

				GUI.color = Color.white;
			}
		};
	}
}
