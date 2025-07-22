#include <GL/glut.h>
#include <math.h>
#define pi 3.1415926

GLint windows_width = 800;
GLint windows_height = 800;

GLfloat spin = 0.0f,rotatev=0.025f;
GLfloat cameraX = 0.0f, cameraY = 0.0f, cameraZ = 3.0f;
GLfloat cameraAngleFai = pi / 2, cameraAngleTheta = pi;
GLfloat upx = 0.0f, upy = 1.0f, upz = 0.0f;
bool enable_camera_move = true;
void display()
{
	GLfloat r = 1.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ,
			cameraX + sin(cameraAngleTheta) * sin(cameraAngleFai), 
			cameraY + cos(cameraAngleFai), 
			cameraZ + cos(cameraAngleTheta) * sin(cameraAngleFai),
			upx, upy, upz);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect = windows_width * 1.0 / windows_height;
	glViewport(0, 0, windows_width, windows_height);
	if (aspect >= 1)
	{
		gluPerspective(60, windows_width * 1.0 / windows_height, 0.1, 50);
		glMatrixMode(GL_MODELVIEW);
	}
	else
	{
		gluPerspective(60, windows_width * 1.0 / windows_height, 0.1, 50);
		glMatrixMode(GL_MODELVIEW);
		glScalef(aspect, aspect, aspect);
	}


	glRotatef(spin, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0, 1.0, 1.0);
	int nw = 40;//nw表示纬线数量
	int nj = 40;//hj表示经线数量
	//绘制纬线
	for (int i = 0;i <= nw;++i)
	{
		GLfloat  fai= pi*i / nw;
		glBegin(GL_LINE_STRIP);
		int nnw = 180;//nnw表示一条纬线上的折线段数量
		for (int j = 0;j <= nnw;++j)
		{
			GLfloat theta = 2*pi*j / nnw;
			GLfloat x = r * sin(theta) * sin(fai);
			GLfloat y = r * cos(fai); 
			GLfloat z = r * cos(theta) * sin(fai);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	//绘制经线
	for (int i = 0;i <= nj;++i)
	{
		GLfloat  theta = 2.0 * pi * i / nj;
		glBegin(GL_LINE_STRIP);
		int nnj = 180;//nnw表示一条经线上的折线段数量
		for (int j = 1;j < nnj;++j)
		{
			GLfloat fai = pi * j / nnj;
			GLfloat x = r * sin(theta) * sin(fai);
			GLfloat y = r * cos(fai);
			GLfloat z = r * cos(theta) * sin(fai);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	windows_height = h;
	windows_width = w;
	glutPostRedisplay();
}

void idle_func()
{
	spin += rotatev;
	if (spin >= 360) spin -= 360;
	glutPostRedisplay();
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
void init()
{
	glClearColor(0, 0, 0, 1);
	glutWarpPointer(windows_width / 2, windows_height / 2);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windows_width, windows_height);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("线框球体");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_func);
	glutPassiveMotionFunc(motion_func);
	glutMainLoop();

}