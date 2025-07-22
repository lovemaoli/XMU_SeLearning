#include <GL/glut.h>
#include <cmath>
#include <iostream>
const float pi = 3.1415926;
using namespace std;
//颜色集合
GLfloat color[][3] = { {1.0,0,0},
					 {0,1.0,0},
					 {0,0,1.0},
					 {0,1.0,1.0},
					 {1.0,0,1.0},
					 {1.0,1.0,0} };
GLfloat color2[][3] = { {0,107.0/255,176.0/255},
					   {239.0/255,169.0/255,13.0/255},
	                   {29.0/255,24.0/255,21.0/255},
	                   {5.0/255,147.0/255,65.0/255},
	                   {220.0/255,47.0/255,31.0/255},//蓝黄黑绿红
					 };
//圆心集合
GLfloat p[][2] = { {-0.45,0.2},{-0.225,-0},{0,0.2},{0.225,-0},{0.45,0.2} };
GLfloat depth[][4] = { {0,0.8,0.8,0.8},{0.8,0.5,0,0.8},{0,0,0.8,0.5},
	                   {0.8,0.5,0,0.5},{0,0,0.8,0} };
void display()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	for (int i = 0;i < 5;++i)
	{
		glColor3f(color2[i][0], color2[i][1], color2[i][2]);
		const int n = 1000;
		float r[] = { 0.17,0.2 };
		float delta_theta = 2 * pi / n;
		glBegin(GL_QUAD_STRIP);
		for (int k = 0;k <= n;++k)
		{
			int part = ((k + n / 8) % n) / (n / 4);
			for (int j = 0;j < 2;++j)
			{
				float x = p[i][0] + r[j] * cos(delta_theta * k);
				float y = p[i][1] + r[j] * sin(delta_theta * k);
				glVertex3f(x, y,depth[i][part]);
			}
		}
		glEnd();
	}
	glFlush();
	glutSwapBuffers();
}

void init()
{
	glClearColor(1, 1, 1,0);
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		// 窗口的宽度小于或等于高度
		glOrtho(-1.0f, +1.0f, -1.0f * (GLfloat)h / (GLfloat)w, 1.0f * (GLfloat)h / (GLfloat)w,1.0f,-1.0f);
	}
	else
	{
		// 窗口的宽度大于高度
		glOrtho(-1.0f * (GLfloat)w / (GLfloat)h, 1.0f * (GLfloat)w / (GLfloat)h, -1.0f, 1.0f,1.0f,-1.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char** arg)
{
	glutInit(&argc, arg);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("奥运五环");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}