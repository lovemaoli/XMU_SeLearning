#pragma once
#include <stdio.h>

class PPM
{
public:
	PPM(int width=640, int height=480)
	{
		_nWidth = width;
		_nHeight = height;
		_nChannel = 3;
		_rgb_data = new unsigned char[3*_nWidth*_nHeight];
	}

	~PPM(){
		delete []_rgb_data;
	}

	void SetPixel(int row, int col, unsigned r, unsigned g, unsigned b)
	{
		int idx = 3 * (row * _nWidth + col);
		_rgb_data[idx + 0] = r;
		_rgb_data[idx + 1] = g;
		_rgb_data[idx + 2] = b;
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
				idx = 3*(j * _nWidth + i);
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