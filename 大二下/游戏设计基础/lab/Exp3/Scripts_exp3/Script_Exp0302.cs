using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Script_Exp0302 : MonoBehaviour 
{
	void Start()
	{
		StartCoroutine (CreateCube());
	}
	IEnumerator CreateCube()
	{
		for (int i = 0; i < 100; i++) {
			GameObject.CreatePrimitive (PrimitiveType.Cube).transform.position =
				Vector3.one * i;
			yield return new WaitForSeconds(1f);
		}
	}
}
