using UnityEngine;
using UnityEditor;
using System.Reflection;

//与Script_Exp0207只可保留一个
[CustomEditor(typeof(Transform))]
public class Script_Exp0208 : Editor
{
	private Editor m_Editor;
	void OnEnable()
	{
		m_Editor = Editor.CreateEditor(target, Assembly.GetAssembly(typeof(Editor)).GetType("UnityEditor.TransformInspector", true));
	}

	public override void OnInspectorGUI()
	{
		if (GUILayout.Button("拓展Transform1"))
		{
		}
		//开始禁止
		GUI.enabled = false;
		m_Editor.OnInspectorGUI();
		//结束禁止
		GUI.enabled = true;

		if (GUILayout.Button("拓展Transform2"))
		{
		}
	}
}
