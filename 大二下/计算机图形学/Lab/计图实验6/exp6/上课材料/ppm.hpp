#pragma once
#include <stdio.h>
#include <iostream>
using namespace std;
class PPM
{
public:
	PPM(int width = 640, int height = 480)
	{
		_nWidth = width;
		_nHeight = height;
		_nChannel = 3;
		_rgb_data = new unsigned char[3 * _nWidth * _nHeight];
	}

	~PPM() {
		delete[]_rgb_data;
	}

	void SetPixel(int row, int col, unsigned r, unsigned g, unsigned b)
	{
		int idx = 3 * (row * _nWidth + col);
		_rgb_data[idx + 0] = r;
		_rgb_data[idx + 1] = g;
		_rgb_data[idx + 2] = b;
	}


	bool Read_Pixel_from_PPM(const char* filename, int& r, int& g, int& b, int i, int j)
	{
		// 打开文件

		FILE* fp = NULL;
		fopen_s(&fp, filename, "rb");
		if (fp == NULL) {
			printf("Error: failed to open file %s\n", filename);
			return false;
		}

		// 读取 PPM 文件头信息
		char header[64];
		fgets(header, 64, fp);  // 文件类型
		if (header[0] != 'P') {
			printf("Error: invalid PPM file format :%s\n", header);

			fclose(fp);
			return false;
		}
		fgets(header, 64, fp);  // 图像宽度与高度
		int width, height;

		sscanf_s(header, "%d %d", &width, &height);// cout << "w" << " h  " << width << " " << height << endl;
		fgets(header, 64, fp);  // 最大像素值

		for (int jj = height - 1; jj >= j; --jj)
		{
			for (int ii = 0; ii <= i; ++ii)
			{

				char get[40];
				fgets(get, 40, fp);
				if (jj == j && ii == i)
				{
					sscanf_s(get, "%d %d %d", &r, &g, &b);
					//cout << r<<"   " << g<<"   " << b << endl;
				}
				get[0] = '\0';

			}
		}
		// 关闭文件并返回结果
		fclose(fp);
		return true;
	}


	void Write2File(const char* filename = "output.ppm")
	{
		FILE* fp;
		fopen_s(&fp, filename, "w");
		fprintf(fp, "P3\n%d %d\n255\n", _nWidth, _nHeight);
		int idx = 0;
		for (int j = _nHeight - 1; j >= 0; --j)
		{
			for (int i = 0; i < _nWidth; ++i)
			{
				idx = 3 * (j * _nWidth + i);
				fprintf_s(fp, "%d %d %d\n", _rgb_data[idx], _rgb_data[idx + 1], _rgb_data[idx + 2]);
			}
		}

		fclose(fp);
	}

private:
	unsigned char* _rgb_data;
	int _nHeight;
	int _nWidth;
	int _nChannel;
};