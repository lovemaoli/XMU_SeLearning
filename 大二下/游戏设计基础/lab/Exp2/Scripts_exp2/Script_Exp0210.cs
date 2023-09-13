using UnityEngine;

public class Script_Exp0210 : MonoBehaviour
{

	void OnDrawGizmosSelected() //选中Object时绘制Gizmo
	{
		Gizmos.color = Color.red;
		//画线
		Gizmos.DrawLine(transform.position, Vector3.one);
		//立方体
		Gizmos.DrawCube(Vector3.one, Vector3.one);
	}

	void OnDrawGizmos()         //始终绘制Gizmo
	{
		Gizmos.DrawSphere(transform.position, 1);
	}

}
