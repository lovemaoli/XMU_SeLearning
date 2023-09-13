using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Script_Exp0304 : MonoBehaviour 
{
	public float updateInterval = 0.5F;
	private float accum = 0;
	private int frames = 0;
	private float timeleft;
	private string stringFps;
	void Start()
	{
		timeleft = updateInterval;
	}
	void Update()
	{
		timeleft -= Time.deltaTime;
		accum += Time.timeScale / Time.deltaTime;
		++frames;
		if (timeleft <= 0.0) {
			float fps = accum / frames;
			string format = System.String.Format ("{0:F2} FPS", fps);
			stringFps = format;
			timeleft = updateInterval;
			accum = 0.0F;
			frames = 0;
		}
	}
	void OnGUI()
	{
		GUIStyle guiStyle = GUIStyle.none;
		guiStyle.fontSize = 30;
		guiStyle.normal.textColor = Color.red;
		guiStyle.alignment = TextAnchor.UpperLeft;
		Rect rt = new Rect(40, 0, 100, 100);
		GUI.Label(rt, stringFps, guiStyle);
	}
}
