#define NDEBUG
#include <GL/glut.h>
#include<math.h>

#define DEG_TO_RAD 0.017453
const GLfloat RR = 2.0; //camera rad
GLfloat beta = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	//以下语句二选一，看看效果
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	// glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(RR * sin(beta * DEG_TO_RAD), RR * cos(beta * DEG_TO_RAD) * cos(45.0), RR * cos(beta * DEG_TO_RAD) * sin(45),
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	//以下语句绘制三角形，请自行改成绘制立方体
	glBegin(GL_TRIANGLES);
	// face A, part 1
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, -1);
	glEnd();

	// face A, part 2
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0, 0);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glEnd();
	// face B, part 1
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, -1);
	glEnd();
	// face B, part 2
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0.5);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glEnd();
	// face C
	glBegin(GL_TRIANGLES);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, -1, 1);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.5, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glEnd();
	// face D
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0.5);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glEnd();
	// face E
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0, 0.5);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glEnd();
	//face F
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glEnd();

	//glFlush(); /* clear buffers */
	glutSwapBuffers();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	//以下语句设置相机投影参数
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//以下两句二选一，看看效果
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 0.3, 10.0);


	//以下语句设置相机和物体的相对方位
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void idlefunc()
{
	//改变动画参数
	beta += 0.05;
	if (beta > 360) beta -= 360;
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	/*
		1. draw cube:
			draw each face with 2 triangles
		2. adjust view point: 
			modify params in gluLookAt
		3. try to move camera:
			3.1 open depth
				glEnable(GL_DEPTH_TEST);
				glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			3.2 change viewpoint dynamicly 
				3.2.1 load camera in display
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					gluLookAt();
				3.2.2 change angle in idlefunc
					note pre-define constant and angle2rad
			3.3 use double buffer to smooth
				glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
				glutSwapBuffers();
	*/
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
