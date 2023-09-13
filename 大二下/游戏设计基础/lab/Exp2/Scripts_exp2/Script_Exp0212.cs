using UnityEngine;
using UnityEditor;

public class Script_Exp0212
{
	[InitializeOnLoadMethod]
	static void InitializeOnLoadMethod()
	{
		SceneView.duringSceneGui += delegate (SceneView sceneView) {
			Handles.BeginGUI();

			GUI.Label(new Rect(0f, 0f, 50f, 15f), "CJ");
			GUI.Button(new Rect(0f, 20f, 50f, 50f),
				AssetDatabase.LoadAssetAtPath<Texture>("Assets/CJ.jpg"));


			Handles.EndGUI();
		};
	}

}
