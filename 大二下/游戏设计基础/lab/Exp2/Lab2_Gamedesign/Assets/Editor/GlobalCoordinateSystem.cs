using UnityEditor; //用于在编辑器中自定义菜单和编辑器界面
using UnityEngine;
using System.Reflection; //System.Reflection命名空间可以在运行时动态获取程序集信息

[InitializeOnLoad] //在Unity编辑器启动时加载
public class GlobalCoordinateSystem : EditorWindow
{
    private static bool _isEnabled = false; //表示全局坐标系是否启用
    private static GameObject _axes; //全局坐标系的GameObject对象
    private static Transform _selectedAxis; //选中的轴的Transform对象
    private static float _axisLength = 5f; //坐标轴长度，默认为5
    private static float _cubeSize = 0.5f; //尾端立方体大小，默认为0.5

    [MenuItem("拓展全局坐标系_黄勖/Toggle")] //定义菜单项，用于启用和关闭全局坐标系
    public static void Toggle()
    {
        _isEnabled = !_isEnabled; //切换全局坐标系的启用状态
        Debug.Log("Toggle"); //测试
        if (_isEnabled)
        {
            CreateAxes(); //启用全局坐标系
        }
        else
        {
            DestroyAxes(); //关闭全局坐标系
        }
    }

    private static void CreateAxes() //创建全局坐标系
    {
        _axes = new GameObject("Global Coordinate System"); //创建Global Coordinate System的GameObject

        //创建X轴
        var x = new GameObject("X");
        x.transform.SetParent(_axes.transform); //设置X的父物体为全局坐标系
        var lineX = x.AddComponent<LineRenderer>(); //添加LineRenderer组件
        lineX.material = new Material(Shader.Find("Sprites/Default")); //设置材质球
        lineX.startColor = Color.red; //设置线段起始颜色
        lineX.endColor = Color.red; //结束颜色
        lineX.startWidth = 0.1f; //线段起始宽度
        lineX.endWidth = 0.1f; //线段结束宽度
        lineX.SetPosition(0, Vector3.zero); //线段起始点为(0,0,0)
        lineX.SetPosition(1, new Vector3(_axisLength, 0f, 0f)); //线段结束点为(_axisLength,0,0)
        Selection.activeObject = lineX; //将当前对象设置为选中的对象
        var cubeX = GameObject.CreatePrimitive(PrimitiveType.Cube); //创建方体
        cubeX.transform.localScale = new Vector3(_cubeSize, _cubeSize, _cubeSize);//设置立方体缩放大小
        cubeX.transform.SetParent(x.transform);//将立方体设置为X轴的子物体
        cubeX.transform.localPosition = new Vector3(_axisLength, 0f, 0f);//设置立方体位置

        //创建Y轴
        var y = new GameObject("Y");
        y.transform.SetParent(_axes.transform);
        var lineY = y.AddComponent<LineRenderer>();
        lineY.material = new Material(Shader.Find("Sprites/Default"));
        lineY.startColor = Color.green;
        lineY.endColor = Color.green;
        lineY.startWidth = 0.1f;
        lineY.endWidth = 0.1f;
        lineY.SetPosition(0, Vector3.zero);
        lineY.SetPosition(1, new Vector3(0f, _axisLength, 0f));
        var cubeY = GameObject.CreatePrimitive(PrimitiveType.Cube);
        cubeY.transform.localScale = new Vector3(_cubeSize, _cubeSize, _cubeSize);
        cubeY.transform.SetParent(y.transform);
        cubeY.transform.localPosition = new Vector3(0f, _axisLength, 0f);

        //创建Z轴
        var z = new GameObject("Z");
        z.transform.SetParent(_axes.transform);
        var lineZ = z.AddComponent<LineRenderer>();
        lineZ.material = new Material(Shader.Find("Sprites/Default"));
        lineZ.startColor = Color.blue;
        lineZ.endColor = Color.blue;
        lineZ.startWidth = 0.1f;
        lineZ.endWidth = 0.1f;
        lineZ.SetPosition(0, Vector3.zero);
        lineZ.SetPosition(1, new Vector3(0f, 0f, _axisLength));
        var cubeZ = GameObject.CreatePrimitive(PrimitiveType.Cube);
        cubeZ.transform.localScale = new Vector3(_cubeSize, _cubeSize, _cubeSize);
        cubeZ.transform.SetParent(z.transform);
        cubeZ.transform.localPosition = new Vector3(0f, 0f, _axisLength);

        Selection.activeGameObject = _axes;
    }

    private static void DestroyAxes() //销毁坐标轴的游戏对象
    {
        if (_axes != null)
        {
            DestroyImmediate(_axes);
        }
    }

    //自定义 Transform 组件
    [CustomEditor(typeof(Transform))]
    public class GlobalCoordinateSystem_inspect : Editor
    {
        private Editor m_Editor;//存储基础的 Transform 组件的编辑器
        // 当激活该编辑器时，创建一个基础的 Transform 组件的编辑器
        void OnEnable()
        {
            m_Editor = Editor.CreateEditor(target,
                Assembly.GetAssembly(typeof(Editor)).GetType("UnityEditor.TransformInspector", true));
        }

        // 在编辑器中绘制自定义的 Transform 组件的属性
        public override void OnInspectorGUI()
        {
            // 绘制自定义标签
            GUILayout.Label("拓展Transform : 修改全局坐标系");
            GUILayout.Label("22920212204392 黄勖");

            // 使用 EditorGUILayout 绘制一个可以编辑的浮点数，用于控制坐标轴长度
            EditorGUI.BeginChangeCheck();
            var newAxisLength = EditorGUILayout.FloatField("坐标轴长度", _axisLength);

            // 用于控制尾端立方体的大小
            var newCubeSize = EditorGUILayout.FloatField("尾端立方体大小", _cubeSize);

            // 如果用户编辑了任意一个值，重新生成坐标轴
            if (EditorGUI.EndChangeCheck())
            {
                _axisLength = newAxisLength;
                _cubeSize = newCubeSize;

                // 销毁旧的坐标轴
                DestroyAxes();

                // 生成新的坐标轴
                CreateAxes();
            }

            // 调用 Unity 默认的 Transform 组件的编辑器
            m_Editor.OnInspectorGUI();
        }

    }


}