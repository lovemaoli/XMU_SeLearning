using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Script_Exp0301 : MonoBehaviour 
{
	void Awake () 
	{
		Debug.Log ("Awake 初始化并且永远只会执行一次");
	}

	void OnEnable()
	{
		Debug.Log ("OnEnable 脚本每次激活执行一次");
	}

	void Start()
	{
		Debug.Log ("Start 初始化后的下一帧执行，并且永远只会执行一次");
	}

	void OnDisable()
	{
		Debug.Log ("OnDisable 脚本每次反激活执行一次");
	}

	void OnDestroy()
	{
		Debug.Log ("OnDestroy 脚本反初始化并且永远只会执行一次");
	}

	void OnApplicationQuit()
	{
		Debug.Log ("应用程序退出执行一次");
	}
}
