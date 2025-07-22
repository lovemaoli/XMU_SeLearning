#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
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
					vertex.push_back({x,y,z,nx,ny,nz});
				}
				for (int i = 0;i < face_num;++i)
				{
					int v0, v1, v2, v3;
					file >> v0 >> v1 >> v2 >> v3;
					face.push_back({v1,v2,v3});
				}
			}
		}
		file.close();
	}
};

ply p;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (Face face : p.face)
	{
		int ptr[3] = { face.v1,face.v2,face.v3};
		glBegin(GL_TRIANGLES);
		for (int i = 0;i < 3;++i) {
			glVertex3f(p.vertex[ptr[i]].x, p.vertex[ptr[i]].y, p.vertex[ptr[i]].z);
		}glEnd();
	}glutSwapBuffers();
}

void init()
{
	p.read_ply("lizhenxiout.ply");
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
	glColor3f(1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("´¿É«Ð¡ÈË");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

