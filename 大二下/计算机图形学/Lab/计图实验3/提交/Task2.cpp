#include <GL/freeglut.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#define pi 3.1415926
using namespace std;

GLint R = 2000;
GLfloat theta = 0.0f, fai = pi/4;
GLfloat camera_theta = 0.0f, camera_fai = pi / 2;

GLfloat light_pos[4];
GLfloat diffuse0[4] = { 198.0/255,145.0/255,69.0/255,1.0};

GLfloat spin = 0.0f;

struct Vertex
{
	GLfloat x, y, z, nx, ny, nz;
};

struct Face
{
	GLint v1, v2, v3;
};

class ply
{
private:
	ifstream file;
public:
	int vertex_num;
	int face_num;
	vector<Vertex> vertex;
	vector<Face> face;
	void read_ply(string file_path)
	{
		file.open(file_path, ios::in);
		if (!file.is_open()) exit(0);
		string line;
		while (getline(file, line))
		{
			if (line.find("element vertex ") != string::npos)	vertex_num = stoi(line.substr(15));
			if (line.find("element face ") != string::npos)		face_num = stoi(line.substr(13));
			if (line.find("end_header") != string::npos)
			{
				for (int i = 0;i < vertex_num;++i)
				{
					float x, y, z, nx, ny, nz;
					file >> x >> y >> z >> nx >> ny >> nz;
					vertex.push_back({ x,y,z,nx,ny,nz });
				}
				for (int i = 0;i < face_num;++i)
				{
					int v0, v1, v2, v3;
					file >> v0 >> v1 >> v2 >> v3;
					face.push_back({ v1,v2,v3 });
				}
			}
		}
		file.close();
	}
};

ply p;

void display()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	gluLookAt(0, 0, 2200, 0, 0, 0, 0, 1, 0);
	glRotatef(camera_theta, 0, 1, 0);
	glRotatef(camera_fai, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0, 0, 1100);
	for (Face face : p.face)
	{
		int ptr[3] = { face.v1,face.v2,face.v3 };
		glBegin(GL_TRIANGLES);
		for (int i = 0;i < 3;++i) {
			glNormal3f(p.vertex[ptr[i]].nx, p.vertex[ptr[i]].ny, p.vertex[ptr[i]].nz);
			glVertex3f(p.vertex[ptr[i]].x, p.vertex[ptr[i]].y, p.vertex[ptr[i]].z);
		}glEnd();
	}

	glPopMatrix();
	glutSwapBuffers();
}

void init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1, 0.1, 5000);
	glMatrixMode(GL_MODELVIEW);
}

void idle_func()
{
	theta += 0.10f;
	light_pos[0] = R * sin(theta) * sin(fai);
	light_pos[1] = R * cos(fai);
	light_pos[2] = R * cos(theta) * sin(fai);
	light_pos[3] = 1.0f;
	glutPostRedisplay();
}

void key_func(unsigned char key, int x, int y)
{
	GLfloat movespeed = 30.0f;
	switch (key)
	{
	case 27:exit(0);break;
	case 's':camera_fai += movespeed;break;
	case 'w':camera_fai -= movespeed;break;
	case 'a':camera_theta -= movespeed;break;
	case 'd':camera_theta += movespeed;break;
	default:break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("¹âÕÕÐ¡ÈË");
	p.read_ply("lizhenxiout.ply");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);
	glutKeyboardFunc(key_func);
	glutMainLoop();
}

