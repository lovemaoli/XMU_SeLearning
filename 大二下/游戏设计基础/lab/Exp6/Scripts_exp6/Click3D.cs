using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.Events;

public class Click3DEvent : UnityEvent<GameObject,PointerEventData>{}


public class Click3D:MonoBehaviour,IPointerClickHandler
{
	public static Click3DEvent click3DEvent = new Click3DEvent();

	//检测是否发生了点击
	public void OnPointerClick(PointerEventData eventData)
    {
		//输出以控制单击的GameObject的名称和以下消息。单击GameObject时，可以将其替换为您自己的操作。
		//Debug.Log("Game Object Clicked！");
		click3DEvent.Invoke(gameObject, eventData);
	}
}

