using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(Camera))]
public class Script_Exp0206 :Editor
{
	public override void OnInspectorGUI(){
		if (GUILayout.Button ("拓展Camera1")) {
			Debug.Log("拓展Camera");
		}

		base.OnInspectorGUI ();
		if (GUILayout.Button ("拓展Camera2")) {
			Debug.Log("拓展Camera");
		}
	}
}