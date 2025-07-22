#include <GL/glut.h>
#include <cmath>
GLfloat spin = 0.0f;
GLfloat dsize = 0.0f;
GLfloat t = 0;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
}

void display(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(dsize, dsize, dsize);
	glRotatef(spin, 0, 0, 1);
	/* A triangle */
	GLfloat vertices[3][2] = { {-1.0,-1.0},{1.0,-1.0},{0.0,1.0} };
	glColor3f(1.0f * rand() / RAND_MAX, 1.0f * rand() / RAND_MAX, 1.0f * rand() / RAND_MAX);
	int j, k;
	GLfloat p[2] = { 0.0,0.0 };  /* an arbitrary initial point inside
							  traingle */
	glClear(GL_COLOR_BUFFER_BIT);  /* clear the window */
	glBegin(GL_POINTS);
	/* compute and plots 5000 new points */
	for (k = 0; k < 50000; k++)
	{
		j = rand() % 3; /* pick a vertex at random */
		/* Compute point halfway between selected vertex and old point */
		p[0] = (p[0] + vertices[j][0]) / 2.0;
		p[1] = (p[1] + vertices[j][1]) / 2.0;

		/* plot new point */
		glVertex2fv(p);
	}
	glEnd();
	glFlush(); /* clear buffers */
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void idlefunc()
{
	spin += 0.05f;
	if (spin >= 360) spin -= 360;
	t += 0.005f;
	dsize = 1 + 0.5*sin(0.5*t);
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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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
