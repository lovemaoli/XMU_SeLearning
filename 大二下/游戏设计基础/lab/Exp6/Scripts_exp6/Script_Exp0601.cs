using UnityEngine;

public class Script_Exp0601 : MonoBehaviour  
{

	void Update()
	{

		//按下空格键
		if (Input.GetKeyDown (KeyCode.Space)) {
			Debug.Log("按下空格");
		}
		//抬起空格键
		if (Input.GetKeyUp (KeyCode.Space)) {
			Debug.Log("抬起空格");
		}
		//按下中空格键
		if (Input.GetKey (KeyCode.Space)) {
			Debug.Log("按住空格");
		}
		//按下鼠标左键，手机上则是按下屏幕
		if (Input.GetMouseButton (0)) {
			Debug.LogFormat ("点击屏幕坐标:{0}", Input.mousePosition);
		}

		//手指触摸屏幕中
		if (Input.touchCount > 0) {
			Touch touch = Input.GetTouch (0);
			//开始触摸
			if (touch.phase == TouchPhase.Began) {
			}
			//触摸移动
			if (touch.phase == TouchPhase.Moved) {
			}
			//触摸结束
			if (touch.phase == TouchPhase.Ended) {
			}
			//是否支持3DTouch
			if (Input.touchPressureSupported) {
				Debug.LogFormat ("3DTouch的力度:{0}", touch.pressure);
			}
		}
	}
}
