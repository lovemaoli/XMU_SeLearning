using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Script_Exp0303 : MonoBehaviour 
{
	IEnumerator CreateCube()
	{
		for (int i = 0; i < 100; i++) {
			GameObject.CreatePrimitive (PrimitiveType.Cube).transform.position =
				Vector3.one * i;
			yield return new WaitForSeconds(1f);
		}
	}

	private Coroutine m_Coroutine = null;

	void OnGUI()
	{
		if (GUILayout.Button ("StartCoroutine")) {
			if (m_Coroutine != null) {
				StopCoroutine (m_Coroutine);
			}
			m_Coroutine = StartCoroutine (CreateCube());
		}
		if (GUILayout.Button ("StopCoroutine")) {
			if (m_Coroutine != null) {
				StopCoroutine (m_Coroutine);
			}
		}
	}
}
