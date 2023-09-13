using UnityEngine;

public class Script_Exp0602 : MonoBehaviour  
{

	void Update()
	{

		if (Input.GetMouseButtonDown (0)) {
			Ray ray = Camera.main.ScreenPointToRay (Input.mousePosition);

			RaycastHit hit;
			if (Physics.Raycast (ray, out hit)) {
				Debug.LogFormat ("Raycast: {0} 3D坐标:{1}", hit.collider.name, hit.point);
			}
		
			RaycastHit[] hits = Physics.RaycastAll (ray);
			foreach (var h in hits) {
				Debug.LogFormat ("RaycastAll: {0} 3D坐标:{1}", hit.collider.name, hit.point);
			}
		}
	}
}
