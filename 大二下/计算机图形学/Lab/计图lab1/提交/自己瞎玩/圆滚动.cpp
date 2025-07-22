#include "GL/glut.h"
#include <cmath>
#include <cstdio>

const double pi = 3.1415926;
GLfloat spin = 0.0;
GLfloat v = 0.0f;
float t = 0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(v, 0, 0);

	glPushMatrix();
	int n = 6;
	double r = 0.3;//r表示半径   
	double xx = 0, yy = 0;//x,y表示圆心坐标
	double color[][3] = { {1.0,0,0},
						 {0,1.0,0},
						 {0,0,1.0},
						 {0,1.0,1.0},
						 {1.0,0,1.0},
						 {1.0,1.0,0}
	};

	for (int i = 0;i < n;++i)//n表示分成几个大的扇形
	{
		int nn = 1000;//n表示一个扇形由多少个三角形进行近似
		double T = 2 * pi / n;//T表示每个扇形对应的圆周角大小
		glColor3f(color[i][0], color[i][1], color[i][2]);
		glBegin(GL_TRIANGLES);
		for (int j = 0;j <= nn;++j)
		{
			glVertex2d(0, 0);
			double theta =spin+i*T+ j*T / nn;
			//图元采用三角形，绘制三点之后由顶点处理器绘制三角形
			double x = xx+r*cos(theta);
			double y = yy+r*sin(theta);
			glVertex2d(x, y);
			theta = spin+i * T + (j+1) * T / nn;
			x = xx+r*cos(theta);
			y = yy+r*sin(theta);
			glVertex2d(x, y);
		}
		glEnd();
	}

	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

void spinDisplay()
{
	spin = -2*sin(0.05*t);
	v = 0.0025 * cos(0.05 * t);
	t += 0.05;//t用于表示时间
	//printf("%lf\n", spin);
	glutPostRedisplay();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	glClearColor (1,1,1,0); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("画一个圆");
	glutDisplayFunc(display);
	glutIdleFunc(spinDisplay);
	//glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	
}
