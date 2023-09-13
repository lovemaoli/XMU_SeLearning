using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RandomObjectSpawner : MonoBehaviour
{
    private GameObject latestObj;
    void Start()
    {
        for (int i=0;i<5;i++)
        {
            //在程序启动时随机创建5个物体分布于随机位置
            if(Random.Range(0,1.0f)>0.5f){
                latestObj = GameObject.CreatePrimitive(PrimitiveType.Cube);//生成立方体
            }else{
                latestObj = GameObject.CreatePrimitive(PrimitiveType.Sphere);//生成球
            }
            //随机设置立方体位置
            latestObj.transform.position = new Vector3(Random.Range(-8, 8), Random.Range(-3, 3), Random.Range(-5, 5));
            //随机设置立方体颜色
            latestObj.GetComponent<Renderer>().material.color = new Color(Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f));
        }
    }

    void Update()
    {
        // 让相机对准的物体做随机运动或缩放
        latestObj.transform.position += new Vector3(Random.Range(-0.05f, 0.05f), Random.Range(-0.05f, 0.05f), Random.Range(-0.05f, 0.05f));        
        latestObj.transform.localScale += new Vector3(Random.Range(-0.05f, 0.05f), Random.Range(-0.05f, 0.05f), Random.Range(-0.05f, 0.05f));    
    }

    int count = 0;
    private void FixedUpdate()
    {
        // 启动后再随机创建5个物体，每隔2秒创建一个
        if(count < 5)
        {
            if(Random.Range(0,1.0f)>0.5f){
                latestObj = GameObject.CreatePrimitive(PrimitiveType.Cube);//生成立方体
            }else{
                latestObj = GameObject.CreatePrimitive(PrimitiveType.Sphere);//生成球
            }
            latestObj.transform.position = new Vector3(Random.Range(-8, 8), Random.Range(-3, 3), Random.Range(-5, 5));
            latestObj.GetComponent<Renderer>().material.color = new Color(Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f));
            count++;
            // 让相机每次都对准新创建的物体，
            GameObject.Find("Main Camera").transform.LookAt(new Vector3(latestObj.transform.position.x, latestObj.transform.position.y, latestObj.transform.position.z));//使相机对准新生成的物体
        }
    }

    private void OnGUI()
    {
        // 通过OnGUI在屏幕右上角显示最新创建物体的名称、位置，大小
        GUI.Label(new Rect(Screen.width - 200, 10, 150, 200), "名称：Object "+count+"\n");
        GUI.Label(new Rect(Screen.width - 200, 25, 150, 200), "位置：(" + latestObj.transform.position.x +","+ latestObj.transform.position.y  + ","+ latestObj.transform.position.z +")"+"\n");
        GUI.Label(new Rect(Screen.width - 200, 55, 150, 200), "边长：" + latestObj.transform.localScale);
    }

}
