#include <GL/glut.h>
#include <cmath>
#include <cstdio>

const double pi = 3.1415926;
GLfloat spin = 0.1;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glRotatef(spin, 0, 0, 1);
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
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(0, 0);
	for (int i = 0;i < n;++i)//n表示分成几个大的扇形
	{
		int nn = 1000;//n表示一个扇形由多少个三角形进行近似
		double T = 2 * pi / n;//T表示每个扇形对应的圆周角大小
		glColor3f(color[i][0], color[i][1], color[i][2]);
		for (int j = 0;j <= nn;++j)
		{
			double theta = i * T + j * T / nn;
			//图元采用三角形，绘制三点之后由顶点处理器绘制三角形
			double x = xx + r * cos(theta);
			double y = yy + r * sin(theta);
			glVertex2d(x, y);
		}
	}
	glEnd();
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

void spinDisplay()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		// 窗口的宽度小于或等于高度
		glOrtho(-1.0f, +1.0f, -1.0f * (GLfloat)h / (GLfloat)w, 1.0f * (GLfloat)h / (GLfloat)w, 1.0f, -1.0f);
	}
	else
	{
		// 窗口的宽度大于高度
		glOrtho(-1.0f * (GLfloat)w / (GLfloat)h, 1.0f * (GLfloat)w / (GLfloat)h, -1.0f, 1.0f, 1.0f, -1.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init()
{
	glClearColor(1, 1, 1, 0);
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
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}
