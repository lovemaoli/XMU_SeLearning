using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.Events;

public class Click3DEvent : UnityEvent<GameObject,PointerEventData>{}

public class Click3D : MonoBehaviour,IPointerClickHandler {

	public static Click3DEvent click3DEvent = new Click3DEvent ();


	#region IPointerClickHandler implementation

	public void OnPointerClick (PointerEventData eventData)
	{
		click3DEvent.Invoke (gameObject, eventData);
	}

	#endregion

}
