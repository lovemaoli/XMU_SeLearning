#include "GL/glut.h"
#include <stdio.h>
#include <math.h>
GLint n = 5;
GLfloat spin = 0.0f;
GLfloat dsize = 0.0f;
GLfloat t = 0;
GLfloat vertices[3][2] = { {0,1},
						  {-0.5*sqrt(3),-0.5},
						  {0.5*sqrt(3),-0.5}};
void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
	glColor3f(1.0f * rand() / RAND_MAX, 1.0f * rand() / RAND_MAX, 1.0f * rand() / RAND_MAX);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
}
void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c,int k)
{
	GLfloat ab[2], ac[2], bc[2];
	if (k)
	{
		for (int j = 0;j < 2;++j) ab[j] = (a[j] + b[j]) / 2;
		for (int j = 0;j < 2;++j) ac[j] = (a[j] + c[j]) / 2;
		for (int j = 0;j < 2;++j) bc[j] = (b[j] + c[j]) / 2;

		divide_triangle(a, ab, ac, k - 1);
		divide_triangle(c, ac, bc, k - 1);
		divide_triangle(b, bc, ab, k - 1);
	}
	else triangle(a, b, c);
}
void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(dsize, dsize, dsize);
	glRotatef(spin, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		divide_triangle(vertices[0],vertices[1],vertices[2],n);
	glEnd();
	glutSwapBuffers();
}

void idle_func()
{
	spin += 0.015f;
	if (spin >= 360) spin -= 360;
	t += 0.005f;
	dsize = 1 + 0.5*sin(0.05*t);
	glutPostRedisplay();
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0, 0, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("??Sierpinski??");
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);
	init();
	glutMainLoop();

}