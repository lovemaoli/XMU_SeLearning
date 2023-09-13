using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(Script_Exp0210))]
public class Script_Exp0211 : Editor
{
    private void OnSceneGUI()
    {
        Handles.BeginGUI();

        if (GUILayout.Button("test", GUILayout.Width(100)))
        {
            Debug.Log(target.name);
        }

        GUILayout.Label(target.name);

        Handles.EndGUI();


    }
}