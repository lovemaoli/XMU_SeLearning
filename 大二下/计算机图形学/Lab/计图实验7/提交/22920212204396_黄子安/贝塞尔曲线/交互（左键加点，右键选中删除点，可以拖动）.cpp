#include "GL/freeglut.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define ColorNum 20
using namespace std;
int width=500,height=500;
GLfloat T = 0.0f;
GLfloat color[ColorNum][3];
bool animation = false;

struct point
{
	float x, y;
	const float range = 0.02f;
	bool operator==(const point& other) const {
		return  (x<other.x + range && x>other.x - range
			&& y<other.y + range && y>other.y - range);
	}
	bool operator=(const point& other)
	{
		x = other.x;
		y = other.y;
		return true;
	}
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
int currentPoint=-1;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
	SetColor();
}
void bezier(float t,const vector<point> pt,int cnt)
{
	if (cnt == 1){
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glPointSize(5.0f);
		glVertex2f(pt[0].x, pt[0].y);
		glEnd();
		curve.push_back(point{ pt[0].x, pt[0].y });
	}
	else{
		if (animation)
		{
			glColor3fv(color[cnt % ColorNum]);
			glBegin(GL_LINE_STRIP);
			for (int i = 0;i < cnt;++i){
				glVertex2f(pt[i].x, pt[i].y);
			}
			glEnd();
		}
		vector<point> tmp;
		for (int i = 0;i < cnt-1;++i){
			float x = (1 - t) * pt[i].x + t * pt[i + 1].x;
			float y = (1 - t) * pt[i].y + t * pt[i + 1].y;
			tmp.push_back(point{x,y});
		}
		bezier(t,tmp,cnt-1);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_WIDTH);
	glLineWidth(1.0);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0;i <= (int) p.size()-1;++i)
	{
		glVertex2f(p[i].x, p[i].y);
	}
	glEnd();
	if (p.size() > 1)
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		if(animation) bezier(T, p, p.size());
		else
		{
			int s = 1000;
			for (int i = 0;i <= s;++i)
			{
				curve.clear();
				bezier(1.0*i/s, p, p.size());
			}
		}
		glLineWidth(1.0);
		glPointSize(1.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = 0;i < curve.size();++i)
		{
			glVertex2f(curve[i].x, curve[i].y);
		}
		glEnd();
	}
	glutSwapBuffers();
}

void idle_func()
{
	T += 0.0001f;
	if (T >= 1.0f) { T = 0;curve.clear(); }
	glutPostRedisplay();
}
void mouse_func(int button,int state,int x,int y)
{
	currentPoint = -1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		float xx = 2.0 * x / width - 1;
		float yy = -2.0 * y / height + 1;
		point pp = { xx,yy };
		for (int i = 0;i < p.size();++i)
		{
			if (p[i] == pp) currentPoint = i;
		}
		if (currentPoint==-1)
		{
			p.push_back(pp);
			T = 0;
			curve.clear();
		}
		glutPostRedisplay();
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		float xx = 2.0 * x / width - 1;
		float yy = -2.0 * y / height + 1;
		point pp = { xx,yy };
		for (int i = 0;i < p.size();++i)
		{
			if (p[i] == pp) currentPoint = i;
		}
		if (currentPoint != -1)
		{
			p.erase(p.begin()+currentPoint);
			T = 0;
			curve.clear();
		}
		glutPostRedisplay();
	}
}
void motion_func(int x,int y)
{
	if (currentPoint !=-1)
	{
		float xx = 2.0 * x / width - 1;
		float yy = -2.0 * y / height + 1;
		point pp = { xx,yy };
		p[currentPoint] = pp;
		if (animation)
		{
			T = 0;
			curve.clear();
		}
		glutPostRedisplay();
	}
}
int main(int argc,char** argv)
{
	cout << "是否保留曲线生成动画[Y/n]：";
	char c;
	while (!(( c = getchar()) == 'Y' || c == 'y' || c == 'N' || c == 'n')) cout << "是否保留曲线生成动画[Y/n]：";
	if (c == 'Y' || c == 'y') animation = true;
	else animation = false;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width,height);
	glutCreateWindow("BezierCurve");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);
	glutMouseFunc(mouse_func);
	glutMotionFunc(motion_func);
	glutMainLoop();
}