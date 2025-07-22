#include <Eigen/Core>
#include <cstdlib>
#include "ppm.hpp"
#include "camera.hpp"
#include "raytracer.hpp"
#include "opencv2/opencv.hpp"
#include <windows.h>
#include <vector>
#include <iostream>
#include <Magick++.h>
using namespace Magick;
using namespace std;
using namespace cv;
int num_samples = 2;

void building_frame(float h, int ii)
{
	char frampath[60];
	int width = 400, height = 300;

	PPM outrlt(width, height);
	PPM inrlt(width, height);
	Camera cam;
	Scene world;
	Sphere sp1(Vector3f(0, h, -2), 1.0);//中心黄色小球
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
	// 打开文件
	FILE* fp = NULL;	int r, g, b;

	if (ii > 3)//文件夹内多于3张图片
	{
		char path[60];
		sprintf(path, "./Frame//frame%d.ppm", ii - 1);
		fopen_s(&fp, path, "rb");
		if (fp == NULL) {
			printf("Error: failed to open file %s\n", path);
			return;
		}

		// 读取 PPM 文件头信息
		char header[64];
		fgets(header, 64, fp);  // 文件类型
		if (header[0] != 'P') {
			printf("Error: invalid PPM file format :%s\n", header);

			fclose(fp);
			return;
		}
		fgets(header, 64, fp);  // 图像宽度与高度


		sscanf_s(header, "%d %d", &width, &height);// cout << "w" << " h  " << width << " " << height << endl;
		fgets(header, 64, fp);  // 最大像素值
	}
	//加运动模糊
	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			if (ii > 3)
			{
				char get[40];
				fgets(get, 40, fp);
				sscanf_s(get, "%d %d %d", &r, &g, &b);
				get[0] = '\0';
			}
			//开始走每个像素
			bool test = false;
			//生成光线
			Vector3f color;
			float u = (i) / (float)(width);
			float v = (j) / (float)(height);
			Ray ray = cam.GenerateRay(u, v);


			color = RayColor(ray, world, test);

			if (ii > 3)//文件夹内多于3张图片
			{
				if (r != color[0] || g != color[1] || b != color[2])
				{
					color[0] = int(255.99 * color[0]) * 0.7 + r * 0.3;
					color[1] = int(255.99 * color[1]) * 0.7 + g * 0.3;
					color[2] = int(255.99 * color[2]) * 0.7 + b * 0.3;
				}

				//cout << "  i" << i << "  j" << j;// << "  color   " << color[0] << " " << color[1] << " " << color[2] << endl;
					//cout << "i" << i << "  j" << j << "  rgb" << r <<" " << g <<" " << b << endl;
				//	cout << "  colorrgb  " << color[0] <<" " << color[1]<<" " << color[2] << endl;

			}
			else
			{
				color[0] = int(255.99 * color[0]);
				color[1] = int(255.99 * color[1]);
				color[2] = int(255.99 * color[2]);
			}
			outrlt.SetPixel(j, i, (int)color[0], (int)color[1], (int)color[2]);
		}
	}
	if (ii > 3)
	{
		fclose(fp);
	}
	sprintf(frampath, "./Frame//frame%d.ppm", ii);
	outrlt.Write2File(frampath);
}

int main()
{
	system("md Frame");//进文件夹
	int n = 100;/////////////////////////////////////
	int count = 0;
	float h = 2.5f, g = -0.0098f, v = 0, x = 0;
	for (int i = 0; i <= n; ++i)
	{
		if (count <= 5)//碰撞次数
		{
			v += g;
			x += v;

			if (x + h <= 0.67)
			{
				v = -0.82 * v;
				count++;
			}
		}
		building_frame(x + h, i);//反正就是一个一个帧生成
	}
	cout << "all finished ！" << endl;

	vector<Image> frames;

	for (int i = 0; i < n; i++)
	{
		char fpath[60];
		sprintf(fpath, "Frame//frame%d.ppm", i);
		cout << "fpath finished ！" << fpath << endl;
		Image image(fpath);
		cout << "image(fpath) finished ！" << endl;
		frames.push_back(image);
	}
	cout << "push_back finished ！" << endl;
	/*将之前生成的一系列 PPM 格式的图像读入内存，保存到一个 vector 容器中，并且使用 Image 类对象封装每个图像。
	其中，sprintf 函数是将字符串按照指定格式组合成新的字符串，这里组合了 "Frame//"、"frame"、i、".ppm" 这四个部分
	，构成新的字符串 framepath，即文件名。然后通过 Image 类的构造函数，将图像读入内存并保存到 frames 容器中
	。最终可以通过遍历 frames 容器，将其合成为一个 GIF 动画*/
	for (int i = 0; i < frames.size(); i++) {
		frames[i].animationDelay(5);
	}
	cout << "animationDela finished ！" << endl;
	/*设置每个帧在动画中持续的时间。对于每个 Image 类对象，调用 animationDelay() 函数并传入一个参数表示延迟的毫秒数，
	这个函数通常用于 GIF 动画，可以控制每帧之间的时间间隔，从而决定动画的播放速度。*/
	string output_file = "output.gif";
	writeImages(frames.begin(), frames.end(), output_file);
	system("rd /s /q Frame");
	/*这一段代码的作用是将之前读入内存的图像合成为一个 GIF 动画，
	并将其写入到名为 "output.gif" 的文件中。其中，writeImages() 函数是 Magick++ 库提供的函数，
	它接受三个参数：frames.begin() 和 frames.end() 是两个迭代器，表示要写入的图片范围，output_file 表示输出的文件名。
	writeImages() 函数会自动根据文件名的后缀来判断输出的文件格式，这里的后缀为 .gif，因此输出的是一个 GIF 动画。
	使用标准库函数 system() 调用系统命令，删除存放生成的 PPM 图像的文件夹 Frame。*/
	return 0;
}