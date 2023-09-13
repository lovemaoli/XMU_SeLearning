using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class HeroControl : MonoBehaviour
{
	public SpriteRenderer heroRenderer;
	public Rigidbody2D heroRigidbody2D;

	void Start()
	{
		TriggerListener.onTriggerEnter2D.AddListener(delegate (GameObject gameObject) {
			Debug.LogFormat("½øÈëÅö×²:{0}", gameObject.name);
		});
		TriggerListener.onTriggerStay2D.AddListener(delegate (GameObject gameObject) {
			Debug.LogFormat("Åö×²ÖÐ:{0}", gameObject.name);
		});
		TriggerListener.onTriggerExit2D.AddListener(delegate (GameObject gameObject) {
			Debug.LogFormat("½áÊøÅö×²:{0}", gameObject.name);
		});
	}

	void Update()
	{
		//´¦Àí·½Ïò¼ü
		if (Input.GetKey(KeyCode.W))
		{
			Run(Vector2.up);
		}
		else if (Input.GetKey(KeyCode.S))
		{
			Run(Vector2.down);
		}
		else if (Input.GetKey(KeyCode.A))
		{
			Run(Vector2.left, true);
		}
		else if (Input.GetKey(KeyCode.D))
		{
			Run(Vector2.right, false);
		}
	}
	void Run(Vector2 position, bool flipx = false)
	{
		//¿ØÖÆÈËÎï×óÓÒÒÆ¶¯Ê±¾µÏñ
		heroRenderer.flipX = flipx;
		//°ó¶¨rigidbodyÒÔºó²»ÄÜÔÚÊ¹ÓÃ transform.position¸³Öµ
		heroRigidbody2D.position += (position * 0.1f);

	}
}

