using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallControl : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    private void OnCollisionEnter(Collision other)
    {
        print("OnCollisionEnter!");
    }
    private void OnCollisionExit(Collision other)
    {
        print("OnCollisionExit!");
    }
    private void OnCollisionStay(Collision other)
    {
        print("OnCollisionStay!");
    }
    public GameObject cube;

    void OnGUI() {
        if (GUILayout.Button ("向左移动物体")) {
            cube.transform.Translate (new Vector3(-0.5f, 0f, 0f));
        }
        if (GUILayout.Button ("向右移动物体")) {
            cube.transform.position = cube.transform.position + new Vector3 (0.5f, 0f, 0f);
        }
        if (GUILayout.Button ("放大物体")) {
            cube.transform.localScale *= 1.2f;
        }
        if (GUILayout.Button ("缩小物体")) {
            cube.transform.localScale *= 0.8f;
        }
    }
}
