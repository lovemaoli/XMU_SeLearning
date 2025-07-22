#include "GL/freeglut.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
const float pi = 3.1415926;
using namespace std;
int width=600,height=600;
float theta = 0, fai = 0,delta=0.02,T=0;
GLdouble objX, objY, objZ;
int idx_i = -1, idx_j = -1,mode=3,t=0;
bool axis = false,animation=true;
void SetPoint();
struct point
{
	float x, y, z;
	const float range = 0.04f;
	bool operator==(const point& other) const {
		return  (x<other.x + range && x>other.x - range
		      && y<other.y + range && y>other.y - range
			  && z<other.z + range && z>other.z - range);
	}
	bool operator=(const point& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return true;
	}
};
float* SetColor(float t)
{
	float a[] = { 0.5,(t + 1) / 2,0.5};
	return a;
}
vector<point> tmp;
void bezier(float t, const vector<point> pt, int cnt)
{
	if (cnt == 1)
	{
		tmp.push_back(point{ pt[0].x, pt[0].y,pt[0].z });
	}
	else
	{
		vector<point> tp;
		for (int i = 0;i < cnt - 1;++i) {
			float x = (1 - t) * pt[i].x + t * pt[i + 1].x;
			float y = (1 - t) * pt[i].y + t * pt[i + 1].y;
			float z = (1 - t) * pt[i].z + t * pt[i + 1].z;
			tp.push_back(point{ x,y,z });
		}
		bezier(t, tp, cnt - 1);
	}
}

vector<vector<point>> p;
vector<vector<point>> curve;
vector<vector<point>> surface;
void drawSurface()
{
	for (int i = 0;i < p.size();++i)
	{
		tmp.clear();
		for (float t = 0;t <= 1;t += delta)
		{
			bezier(t, p[i], p[i].size());
		}
		curve.push_back(tmp);
	}

	for (int i = 0;i < curve[0].size();++i)
	{
		vector<point> s;
		for (int j = 0;j < curve.size();++j) s.push_back(curve[j][i]);

		tmp.clear();
		for (float t = 0;t <= 1;t += delta)
		{
			bezier(t, s, s.size());
		}
		surface.push_back(tmp);
	}
}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	SetPoint();
	drawSurface();
}
void SetPoint()
{
	if (mode == 3)
	{
		p.clear();
		tmp.clear();
		tmp.push_back(point{ -0.5,0.2,0.7 });
		tmp.push_back(point{ 0,-0.5,0.7 });
		tmp.push_back(point{ 0.6,0.1,0.7 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.5,0.4,0 });
		tmp.push_back(point{ 0.0,0.6,0 });
		tmp.push_back(point{ 0.6,0.3,0 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.5,0.3,-0.7 });
		tmp.push_back(point{ 0,0.3,-0.7 });
		tmp.push_back(point{ 0.6,0.6,-0.7 });
		p.push_back(tmp);
	}
	else if (mode == 4)
	{
		p.clear();
		tmp.clear();
		tmp.push_back(point{ -0.5,0.2,0.6 });
		tmp.push_back(point{ 0,-0.5,0.6 });
		tmp.push_back(point{ 0.6,0.1,0.6 });
		tmp.push_back(point{ 0.7,-0.1,0.6 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.5,0.3,0.2 });
		tmp.push_back(point{ 0,0.3,0.2 });
		tmp.push_back(point{ 0.6,0.6,0.2 });
		tmp.push_back(point{ 0.6,0.1,0.2 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.5,0.4,-0.2 });
		tmp.push_back(point{ 0.0,0.6,-0.2 });
		tmp.push_back(point{ 0.6,0.3,-0.2 });
		tmp.push_back(point{ 0.6,0.1,-0.2 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.5,0.3,-0.6 });
		tmp.push_back(point{ 0,0.3,-0.6 });
		tmp.push_back(point{ 0.6,0.6,-0.6 });
		tmp.push_back(point{ 0.6,0.1,-0.6 });
		p.push_back(tmp);
	}
	else if (mode == 5)
	{
		p.clear();
		tmp.clear();
		tmp.push_back(point{ -0.7,0.2,0.7 });
		tmp.push_back(point{ 0,-0.5,0.7 });
		tmp.push_back(point{ 0.2,0.1,0.7 });
		tmp.push_back(point{ 0.4,-0.1,0.7 });
		tmp.push_back(point{ 0.7,-0.1,0.7 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.7,0.3,0.35 });
		tmp.push_back(point{ 0,0.3,0.35 });
		tmp.push_back(point{ 0.4,0.6,0.35 });
		tmp.push_back(point{ 0.4,0.1,0.35 });
		tmp.push_back(point{ 0.6,0.1,0.35 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.7,0.4,0 });
		tmp.push_back(point{ 0.0,0.6,0 });
		tmp.push_back(point{ 0.4,0.3,0 });
		tmp.push_back(point{ 0.4,0.1,0 });
		tmp.push_back(point{ 0.6,0.1,0 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.7,0.3,-0.35 });
		tmp.push_back(point{ 0,0.3,-0.35 });
		tmp.push_back(point{ 0.4,0.6,-0.35 });
		tmp.push_back(point{ 0.4,0.1,-0.35 });
		tmp.push_back(point{ 0.6,0.1,-0.35 });
		p.push_back(tmp);

		tmp.clear();
		tmp.push_back(point{ -0.7,0.3,-0.7 });
		tmp.push_back(point{ 0,0.3,-0.7 });
		tmp.push_back(point{ 0.4,0.6,-0.7 });
		tmp.push_back(point{ 0.4,0.1,-0.7 });
		tmp.push_back(point{ 0.6,0.1,-0.7 });
		p.push_back(tmp);
	}
}
void drawAxis()
{
	glEnable(GL_LINE_WIDTH);
	glLineWidth(3.0);
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0.8, 0, 0);
	glutSolidCube(0.05);
	glPopMatrix();
	glBegin(GL_LINES);
	glVertex3f(-0.8, 0, 0);
	glVertex3f(0.8, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0.8, 0);
	glutSolidCube(0.05);
	glPopMatrix();
	glBegin(GL_LINES);
	glVertex3f(0, -0.8, 0);
	glVertex3f(0, 0.8, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0, 0.8);
	glutSolidCube(0.05);
	glPopMatrix();
	glBegin(GL_LINES);
	glVertex3f(0, 0, -0.8);
	glVertex3f(0, 0, 0.8);
	glEnd();

}

void view()
{
	glRotatef(theta / pi * 180, 0, 1,0);
	glRotatef(fai / pi * 180, 1, 0, 0);
}
void display()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	view();
	if(axis) drawAxis();

	glColor3f(1.0, 0, 0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);//绘制控制点
	for (int i = 0;i < p.size();++i)
	{
		for (int j = 0;j < p[i].size();++j)
		{
			glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
		}
	}
	glEnd();

	//绘制贝塞尔曲线和折线段
	for (int i = 0;i < curve.size();++i)
	{
		if (axis)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_STRIP);
			for (int j = 0;j < p[i].size();++j)
			{
				glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
			}
			glEnd();
		}

		glColor3f(0.5, 0.5, 1.0);
		glBegin(GL_LINE_STRIP);
		for (int j = 0;j < curve[i].size();++j)
		{
			glVertex3f(curve[i][j].x, curve[i][j].y, curve[i][j].z);
		}
		glEnd();
	}

	//绘制曲面
	for (int i = 0;i < t;++i)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j = 0;j < surface[i].size();++j)
		{
			glColor3fv(SetColor(surface[i][j].z));
			glVertex3f(surface[i][j].x, surface[i][j].y, surface[i][j].z);
			if(i>0) glVertex3f(surface[i-1][j].x, surface[i-1][j].y, surface[i-1][j].z);
		}
		glEnd();
	}

	if (animation)
	{
		if(t>0) t -= 1;
		//绘制扫描线上的控制点
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (int i = 0;i < curve.size();++i)
		{
			glColor3f(1.0, 0, 0);
			glVertex3f(curve[i][t].x, curve[i][t].y, curve[i][t].z);
		}
		glEnd();

		//绘制扫描线上控制点连成的折线
		glBegin(GL_LINE_STRIP);
		for (int i = 0;i < curve.size();++i)
		{
			glColor3f(0.5, 1, 1);
			glVertex3f(curve[i][t].x, curve[i][t].y, curve[i][t].z);
		}
		glEnd();

		//绘制扫描线
		glEnable(GL_LINE_WIDTH);
		glLineWidth(2.0);
		glBegin(GL_LINE_STRIP);
		for (int j = 0;j < surface[t].size();++j)
		{
			glColor3f(1, 0.5, 0);
			glVertex3f(surface[t][j].x, surface[t][j].y, surface[t][j].z);
		}
		glEnd();
		t++;
	}

	glutSwapBuffers();
}
void idle_func()
{
	if (animation == true)
	{
		T += 0.0001 / delta;
		t = (int)T;
		if (t >= surface.size()) T = 0;
	}
	else
	{
		t = surface.size();
	}
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	float cameraSpeed = 0.1f;

	switch (key)
	{
	case 'w':
		fai -= cameraSpeed;
		break;

	case 's':
		fai += cameraSpeed;
		break;

	case 'a':
		theta -= cameraSpeed;
		break;

	case 'd':
		theta += cameraSpeed;
		break;
	case 'e':
		mode += 1;
		if (mode == 6) mode = 3;
		SetPoint();
		curve.clear();
		surface.clear();
		drawSurface();
		break;
	case 'q':
		animation = !animation;
		break;
	}
	if (theta > pi / 3) theta = pi / 3;
	if (theta < -pi / 3) theta = -pi / 3;
	if (fai > pi / 3) fai = pi / 3;
	if (fai < -pi / 3) fai = -pi / 3;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	idx_i = -1;idx_j = -1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX, winY, winZ;

		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &objX, &objY, &objZ);
		for (int i = 0;i < p.size();++i)
		{
			for (int j = 0;j < p[i].size();++j)
			{
				if (p[i][j] == point{ (float)objX,(float)objY,(float)objZ })
				{
					idx_i = i;idx_j = j;
				}
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		axis = !axis;
	}
}

void motion_func(int x,int y)
{
	if (idx_i!=-1&&idx_j!=-1)
	{
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX, winY, winZ;
		GLdouble xx,yy,zz;
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &xx, &yy, &zz);
		
		p[idx_i][idx_j] = point{ (float)xx,(float)yy, (float)zz };
		curve.clear();
		surface.clear();
		drawSurface();
		glutPostRedisplay();
	}
}
int main(int argc,char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width,height);
	glutCreateWindow("wsad切换视角，e改控制点个数，右键显示/隐藏坐标系,q停止/播放动画");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle_func);
	glutMouseFunc(mouse);
	glutMotionFunc(motion_func);
	glutMainLoop();
}