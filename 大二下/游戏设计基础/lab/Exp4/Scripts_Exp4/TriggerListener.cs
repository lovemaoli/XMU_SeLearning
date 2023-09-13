using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class TriggerEvent  : UnityEvent<GameObject>{}

public class TriggerListener : MonoBehaviour 
{
	public static TriggerEvent onTriggerEnter2D = new TriggerEvent();
	public static TriggerEvent onTriggerStay2D = new TriggerEvent();
	public static TriggerEvent onTriggerExit2D = new TriggerEvent();

	void OnTriggerEnter2D(Collider2D other) 
	{
		onTriggerEnter2D.Invoke(gameObject);
	}
	void OnTriggerStay2D(Collider2D other) 
	{
		onTriggerStay2D.Invoke (gameObject);
	}
	void OnTriggerExit2D(Collider2D other) 
	{
		onTriggerExit2D.Invoke (gameObject);
	}
}
