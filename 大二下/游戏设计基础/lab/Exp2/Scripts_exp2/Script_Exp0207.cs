using UnityEngine;
using UnityEditor;
using System.Reflection;

//与Script_Exp0208只可保留一个
[CustomEditor(typeof(Transform))]
public class Script_Exp0207 : Editor
{
	private Editor m_Editor;
	void OnEnable()
	{
		m_Editor = Editor.CreateEditor(target,
			Assembly.GetAssembly(typeof(Editor)).GetType("UnityEditor.TransformInspector", true));
	}

	public override void OnInspectorGUI()
	{
		if (GUILayout.Button("拓展Transform"))
		{
		}
		//调用系统绘制方法
		m_Editor.OnInspectorGUI();
		//		base.OnInspectorGUI ();
	}
}
