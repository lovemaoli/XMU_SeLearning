#include <GL\glut.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#define pi 3.1415926
using namespace std;
GLfloat spin = 0.0f;
bool enableSlider = false;
class Slider
{
private:
	static const GLfloat slider_r, width, hight;
	GLfloat slider_x, slider_y;
	GLfloat r_x, r_y;
	GLfloat value;
	GLfloat color[3];
public:
	Slider(GLfloat x,GLfloat y,GLfloat v,GLfloat r,GLfloat g,GLfloat b)
	{
		slider_x = x;slider_y = y;
		value = v;
		r_x = (value - 0.5) * width * 2+x;r_y = y;
		color[0] = r;color[1] = g;color[2] = b;
	}
	void draw_slider()
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glShadeModel(GL_FLAT);
		glColor3fv(color);

		glBegin(GL_QUADS);
		glVertex2f(slider_x + width / 2, slider_y+hight/2);
		glVertex2f(slider_x + width / 2, slider_y - hight / 2);
		glVertex2f(slider_x - width / 2, slider_y - hight / 2);
		glVertex2f(slider_x - width / 2, slider_y + hight / 2);
		glEnd();

		glBegin(GL_POLYGON);
		int n = 60;
		GLfloat slider_r = 0.025f, delta_theta = 2.0 * pi / n;
		for (int i = 0;i <= n;++i)
		{
			GLfloat x = r_x + slider_r * cos(delta_theta * i);
			GLfloat y = r_y + slider_r * sin(delta_theta * i);
			glVertex2f(x, y);
		}
		glEnd();
		glPopMatrix();
	}

	GLfloat getvalue()
	{
		return value;
	}

	void change(GLfloat x,GLfloat y)
	{
		if (y>=slider_y-5*hight&&y<=slider_y+5*hight&&x>=slider_x-width*0.55&&x<=slider_x+width*0.55)
		{
			if (x > width/2+slider_x) r_x=width/2+slider_x;
			else if (x < -width/2+slider_x) r_x=-width/2+slider_x;
			else r_x = x;
			value = (r_x- slider_x) / width*2 + 0.5;
		}
		draw_slider();
	}

	void valueChange(GLfloat v)
	{
		value = v;
		r_x = (value - 0.5) * width+ slider_x;
	}
};
const float Slider::slider_r = 0.0025f,Slider::width=0.4f,Slider::hight=0.01f;

Slider slider1(0.7, 1 - 0.1, 0.5, 1, 0, 0);
Slider slider2(0.7, 1 - 0.2, 0.5, 0, 1, 0);
Slider slider3(0.7, 1 - 0.3, 0.5, 0, 0, 1);
Slider slider4(-0.7, 1 - 0.1, 0.5, 1, 0, 0);
Slider slider5(-0.7, 1 - 0.2, 0.5, 0, 1, 0);
Slider slider6(-0.7, 1 - 0.3, 0.5, 0, 0, 1);

struct Materical
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
};
Materical brass = {
	{0.33,0.22,0.03,1.0},
	{0.78,0.57,0.11,1.0},
	{0.99,0.91,0.81,1.0},
	27.8
};
Materical redPlastic = {
	{0.3,0.0,0.0,1.0},
	{0.6,0.0,0.0,1.0},
	{0.8,0.6,0.6,1.0},
	32.0
};
Materical whiteShiny = {
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0},
	100.0
};

struct Light
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
}l;

Light whiteLight = {
	{0.0,0.0,0.0,1.0},
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0}
};

GLfloat cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.0f;
GLfloat cameraAngleFai = pi/2, cameraAngleTheta = 0;
GLfloat upx = 0.0f, upy = 1.0f, upz = 0.0f;


bool enable_camera_move = true;
struct Mouse
{
	int X, Y;
}mouse;

GLint windows_width = 800;
GLint windows_height = 800;
GLfloat camera_R = 2.0f;

Materical m;
void matrial(int mode)
{
	switch (mode)
	{
	case 0:m = brass;break;
	case 1:m = redPlastic;break;
	case 2:m = whiteShiny;break;
	}
	slider1.valueChange(m.diffuse[0]);
	slider2.valueChange(m.diffuse[1]);
	slider3.valueChange(m.diffuse[2]);
}
void drawCube()
{
	struct point
	{
		GLfloat x, y, z;
	};
	const GLfloat a = 0.5f;
	point p[] = { {a,a,a},{a,a,-a},{-a,a,-a},{-a,a,a},{a,-a,a},{a,-a,-a}, {-a,-a,-a},{-a,-a,a}};
	int face[][4] = { {0,1,2,3},{0,1,5,4},{1,2,6,5},{2,3,7,6},{0,3,7,4},{4,5,6,7} };
	GLfloat normal[][3] = { {0,1.0,0},{1.0,0,0},{0,0,-1.0},{-1.0,0,0},{0,0,1.0},{0,-1.0,0} };
	for (int i = 0;i < 6;++i)
	{
		glNormal3fv(normal[i]);
		glBegin(GL_POLYGON);
		for (int j = 0;j < 4;++j)
		{
			glVertex3f(p[face[i][j]].x, p[face[i][j]].y, p[face[i][j]].z);
		}
		glEnd();
	}
}

void light(int mode)
{
	if (mode == 1)
	{
		for (int i = 0;i < 3;++i)
		{
			l.diffuse[i] = rand() * 1.0f / RAND_MAX;
		}
	}else
	{
		l = whiteLight;
	}	
	slider4.valueChange(l.diffuse[0]);
	slider5.valueChange(l.diffuse[1]);
	slider6.valueChange(l.diffuse[2]);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	l.ambient[0] = slider4.getvalue();
	l.ambient[1] = slider5.getvalue();
	l.ambient[2] = slider6.getvalue();
	glLightfv(GL_LIGHT0, GL_AMBIENT, l.ambient);

	GLfloat R = 0.2f;

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cameraX + camera_R * sin(cameraAngleTheta) * sin(cameraAngleFai),
		cameraY + camera_R * cos(cameraAngleFai),
		cameraZ + camera_R * cos(cameraAngleTheta) * sin(cameraAngleFai),
		cameraX, cameraY, cameraZ,
		upx, upy, upz);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 3000);

	m.diffuse[0] = slider1.getvalue();
	m.diffuse[1] = slider2.getvalue();
	m.diffuse[2] = slider3.getvalue();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m.ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m.specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.shininess);


	glMatrixMode(GL_MODELVIEW);
	glRotatef(80, 1, 1, 1);
	glRotatef(spin, -1, 1, -1);
	drawCube();

	slider1.draw_slider();
	slider2.draw_slider();
	slider3.draw_slider();
	slider4.draw_slider();
	slider5.draw_slider();
	slider6.draw_slider();

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
	matrial(0);
	light(0);
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

		case 'b':matrial(0);break;
		case 'n':matrial(1);break;
		case 'm':matrial(2);break;

		case 'p':light(1);break;
		case 'o':light(0);break;

		default:break;
		}
	}
	if (key == 'l') enable_camera_move=!enable_camera_move;
	glutPostRedisplay();
}

void passive_motion_func(int x, int y)
{
	if (enable_camera_move)
	{
		if (x < 600 && x>200 && y > 200 && y < 600)
		{
			cameraAngleTheta = 0.0f - pi * (x - windows_width / 2) / (windows_width / 2);
			cameraAngleFai = pi / 2 - pi / 2 * (y - windows_height / 2) / (windows_height / 2);
		}
	}
}

void motion_func(int x,int y)
{
	GLfloat winx = (x-windows_width/2) * 1.0 /windows_width * 2;
	GLfloat winy = -(y-windows_height/2) * 1.0 / windows_height * 2;

	slider1.change(winx,winy);
	slider2.change(winx, winy);
	slider3.change(winx, winy);
	slider4.change(winx, winy);
	slider5.change(winx, winy);
	slider6.change(winx, winy);
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
	glutMotionFunc(motion_func);
	glutPassiveMotionFunc(passive_motion_func);
	glutKeyboardFunc(key_func);
	glutMainLoop();
}