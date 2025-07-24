#include <GL\glut.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#define pi 3.1415926
using namespace std;
const GLfloat a = 0.5f;
GLfloat spin = 0.0f;

GLfloat cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f;
GLfloat cameraAngleFai = pi / 2, cameraAngleTheta = pi;
GLfloat upx = 0.0f, upy = 1.0f, upz = 0.0f;

GLint mouseX, mouseY;
bool enable_camera_move = true;

GLint windows_width = 800;
GLint windows_height = 800;

struct point
{
	GLfloat x, y, z;
};

GLfloat color[][3] = { {1,1,0},{1,0,0},{0,1,0},{234.0/255,119.0/255,27.0/255},{0,0,1},{1,1,1} };
//顶点数组
point p[]= { {a,a,a},{a,a,-a},{-a,a,-a},{-a,a,a},
	         {a,-a,a},{a,-a,-a}, {-a,-a,-a},{-a,-a,a} };
//面的顶点数组
int face[][4] = {{0,1,2,3},{0,1,5,4},{1,2,6,5},{2,3,7,6},{0,3,7,4},{4,5,6,7}};

void display()
{
	GLfloat R = 0.1f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cameraX, cameraY, cameraZ,
			  cameraX + sin(cameraAngleTheta) * sin(cameraAngleFai), 
			  cameraY + cos(cameraAngleFai), 
		      cameraZ + cos(cameraAngleTheta) * sin(cameraAngleFai),
		      upx, upy, upz);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 30);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(a, a, a);
	glRotatef(80, 1, 1, 1);
	glRotatef(spin, -1, 1, -1);
	for (int i = 0;i < 6;++i)
	{
		glColor3f(color[i][0], color[i][1], color[i][2]);
		glBegin(GL_POLYGON);
		for (int j = 0;j < 4;++j)
		{
			glVertex3f(p[face[i][j]].x, p[face[i][j]].y, p[face[i][j]].z);
		}
		glEnd();
	}

	glutSwapBuffers();
}
void idle_func()
{
	spin += 0.02f;
	if (spin >= 360) spin -= 360;
	glutPostRedisplay();
}
void init()
{
	glClearColor(0, 0, 0, 1.0);
	glShadeModel(GL_FLAT);
	glutWarpPointer(windows_width / 2, windows_height / 2);
}
void key_func(unsigned char key, int x, int y)
{
	GLfloat movespeed = 0.25f;
	if (enable_camera_move)
	{
		switch (key)
		{
		case 27:exit(0);break;
		case 's':cameraZ += movespeed;break;
		case 'w':cameraZ -= movespeed;break;
		case 'a':cameraX -= movespeed;break;
		case 'd':cameraX += movespeed;break;
		case 'q':cameraY += movespeed;break;
		case 'e':cameraY -= movespeed;break;
		default:break;
		}
	}
	if (key == 'l') enable_camera_move=!enable_camera_move;
	glutPostRedisplay();
}

void motion_func(int x, int y)
{
	if (enable_camera_move)
	{
		cameraAngleTheta = pi - pi / 4 * (x - windows_width / 2) / (windows_width / 2);
		cameraAngleFai = pi / 2 + pi / 4 * (y - windows_height / 2) / (windows_height / 2);
	}
}

int main(int argc,char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(windows_width, windows_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("旋转正方体");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);
	glutPassiveMotionFunc(motion_func);
	glutKeyboardFunc(key_func);
	glutMainLoop();
}