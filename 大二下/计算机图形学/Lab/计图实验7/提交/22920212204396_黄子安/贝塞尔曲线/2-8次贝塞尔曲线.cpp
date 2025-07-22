#include "GL/freeglut.h"
#include <iostream>
#include <cmath>
#include <vector>
#define ColorNum 20
using namespace std;
int n = 8;
GLfloat T = 0.0f;
GLfloat color[20][3];
bool enableLine = true;
struct point
{
	float x, y;
};

void SetColor()
{
	for (int i = 0;i < ColorNum;++i)
	{
		color[i][0] = 1.0 * rand() / RAND_MAX;
		color[i][1] = 1.0 * rand() / RAND_MAX;
		color[i][2] = 1.0 * rand() / RAND_MAX;
	}
}
vector<point> p;
vector<point> curve;
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
	p.push_back(point{ -0.5, 0.5 });
	p.push_back(point{ -0.6, 0 });
	p.push_back(point{ -0.4, -0.3 });
	p.push_back(point{ 0.3, -0.55 });
	p.push_back(point{ 0.4, -0.5 });
	p.push_back(point{ 0.6, -0.2 });
	p.push_back(point{ 0.3, 0.0 });
	p.push_back(point{ 0.4, 0.4 });
	p.push_back(point{ 0.8, 0.9 });
	SetColor();
}
void bezier(float t, const vector<point> pt, int cnt)
{
	if (cnt == 1) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glPointSize(5.0f);
		glVertex2f(pt[0].x, pt[0].y);
		glEnd();
		curve.push_back(point{ pt[0].x, pt[0].y });
	}
	else {
		if (enableLine)
		{
			glColor3fv(color[cnt % ColorNum]);
			glBegin(GL_LINE_STRIP);
			for (int i = 0;i < cnt;++i) {
				glVertex2f(pt[i].x, pt[i].y);
			}
			glEnd();
		}
		vector<point> tmp;
		for (int i = 0;i < cnt - 1;++i) {
			float x = (1 - t) * pt[i].x + t * pt[i + 1].x;
			float y = (1 - t) * pt[i].y + t * pt[i + 1].y;
			tmp.push_back(point{ x,y });
		}
		bezier(t, tmp, cnt - 1);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_WIDTH);
	glLineWidth(1.0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0;i <= n;++i)
	{
		glVertex2f(p[i].x, p[i].y);
	}
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	bezier(T, p, n + 1);

	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0;i < curve.size();++i)
	{
		glVertex2f(curve[i].x, curve[i].y);
	}
	glEnd();

	glutSwapBuffers();
}

void idle_func()
{
	T += 0.0001f;
	if (T >= 1.0f)
	{
		T -= 1.0f;
		curve.clear();
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	cout << "请输入贝塞尔曲线的阶数(1-8):" << endl;
	while (cin >> n && (n > 9 || n < 1))
	{
		cout << "输入阶数不在指定范围内,请重新输入:" << endl;
	};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("BezierCurve");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);
	glutMainLoop();
}