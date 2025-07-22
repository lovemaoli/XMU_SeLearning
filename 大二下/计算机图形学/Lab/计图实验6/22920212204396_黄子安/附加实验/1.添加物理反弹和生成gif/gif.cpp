#include <Eigen/Core>
#include "ppm.hpp"
#include "camera.hpp"
#include "raytracer.hpp"
#include <windows.h>
#include <vector>
#include <iostream>
#include <Magick++.h>
using namespace Magick;
using namespace std;
vector<PPM> ppm_list;
void make_frame(float h,int i)
{
	int width = 640, height = 480;
	PPM outrlt(width, height);
	Camera cam;
	Scene world;
	Sphere sp1(Vector3f(0, h, -2), 1.0);
	Sphere sp2(Vector3f(0, -10000.5, -2), 10000.0);
	Sphere sp3(Vector3f(-2.0, 0, -2), 0.5);
	Sphere sp4(Vector3f(1.0, -0.2, -1.0), 0.3);
	Sphere sp5(Vector3f(3.0, 0, -2.2), 0.4);
	Sphere sp6(Vector3f(-1, 0.0, -0.8), 0.2);

	Material mtl, mtl2, mtl3, mtl4, mtl5;//mLx
	mtl.SetKa(Vector3f(0.5, 0.5, 0.5));//中心黄色小球
	mtl.SetKd(Vector3f(0.8, 0.6, 0.0));
	mtl.SetKs(Vector3f(0.7, 0.8, 0.8));
	mtl.SetTransparent(false);
	mtl.SetReflective(true);
	mtl.SetShiness(50);

	mtl2.SetKa(Vector3f(0.5, 0.5, 0.5));//应该是看不见的
	mtl2.SetKd(Vector3f(0.0, 0.6, 0.2));
	mtl2.SetKs(Vector3f(0.1, 1.0, 0.8));
	mtl2.SetTransparent(false);
	mtl2.SetReflective(false);
	mtl2.SetShiness(10);

	mtl3.SetKa(Vector3f(0.5, 0.5, 0.5));//蓝色小球
	mtl3.SetKd(Vector3f(0.0, 0.3, 0.6));
	mtl3.SetKs(Vector3f(0.0, 0.0, 0.0));
	mtl3.SetTransparent(false);
	mtl3.SetReflective(false);
	mtl3.SetShiness(10);

	mtl4.SetKa(Vector3f(0.1, 0.1, 0.1));//右侧黑色小球
	mtl4.SetKd(Vector3f(0.0, 0.0, 0.0));
	mtl4.SetKs(Vector3f(0.0, 0.0, 0.0));
	mtl4.SetTransparent(true);
	mtl4.SetReflective(false);
	mtl4.SetRefraction(1.33);
	mtl4.SetShiness(200);

	mtl5.SetKa(Vector3f(0.5, 0.5, 0.5));//右侧黄色小球
	mtl5.SetKd(Vector3f(0.75, 0.56, 0.0));
	mtl5.SetKs(Vector3f(0.75, 0.56, 0.0));
	mtl5.SetTransparent(false);
	mtl5.SetReflective(false);
	mtl5.SetRefraction(1.33);
	mtl5.SetShiness(100);

	world.Insert(make_pair(sp1, mtl));
	world.Insert(make_pair(sp2, mtl2));
	world.Insert(make_pair(sp3, mtl3));
	world.Insert(make_pair(sp4, mtl4));
	world.Insert(make_pair(sp5, mtl5));

	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			bool test = false;
			//生成光线
			float u = float(i) / float(width);
			float v = float(j) / float(height);
			Ray ray = cam.GenerateRay(u, v);
			Vector3f color = RayColor(ray, world, test);

			outrlt.SetPixel(j, i,
				int(255.99 * color[0]), int(255.99 * color[1]), int(255.99 * color[2]));
		}
	}
	//ppm_list.push_back(outrlt);
	char path[50];
	sprintf(path, "./Frame//frame%d.ppm", i);
	outrlt.Write2File(path);
}
void add_vague()
{

}
int main()
{
	system("md Frame");
	int n = 150,cnt=0;//cnt为最多的弹跳次数
	float h=4.0f,g=-0.0098f,v=0,x=0,k=0.6;//k为弹性系数
	for (int i = 0;i <= n;++i)
	{
		if (cnt <= 8)
		{
			x += v + 1.0 / 2 * g;
			v += g;
			if (x + h < 0.5)
			{
			
				v = -k * v;cnt++;
			}
		}
		make_frame(x + h, i);

		cout << "Frame " << i << " finished" << endl;
	}
	cout << "Waiting for Gif" << endl;
	vector<Image> frames;
	for (int i = 0;i < n;++i)
	{
		char path[50];
		sprintf(path, "Frame//frame%d.ppm", i);
		Image image(path);
		frames.push_back(image);
	}

	for (int i = 0; i < frames.size(); i++) {
		frames[i].animationDelay(5); 
	}

	string output_file = "Output.gif";
	writeImages(frames.begin(), frames.end(), output_file);
	system("rd /s /q Frame");

	return 0;         
}