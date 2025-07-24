// #define NDEBUG
#include <GL/glut.h>
#include <Eigen/Core>
#include <iostream>
#include <vector>
#include "MyTransform.hpp"

using namespace std;

int WinSizeW;
int WinSizeH;

Eigen::Matrix4f mModelView;
Eigen::Matrix4f mProjection;
Eigen::Matrix4f mViewPort;

//到今天这节课，你应该要能实现如下函数
//Eigen::Matrix4f myRotateX(float angle);
//Eigen::Matrix4f myRotateY(float angle);
//Eigen::Matrix4f myRotateZ(float angle);
//Eigen::Matrix4f myTranslate(float x, float y, float z);
//Eigen::Matrix4f myRotate(float angle, float x, float y, float z);
//Eigen::Matrix4f myFrustum(float left, float right, float bottom, float top, float near, float far);
//Eigen::Matrix4f myOrtho(float left, float right, float bottom, float top, float near, float far);
//Eigen::Matrix4f myViewPort(float x, float y, float w, float h);
//Eigen::Matrix4f myLookAt(float eyex, float eyey, float eyez, 
//						float lookx, float looky, float lookz, 
//						float upx, float upy, float upz);


void SetViewPortMatrix()
{
	mViewPort.setZero();
	mViewPort(0, 0) = 250.0;
	mViewPort(1, 1) = 250.0;
	mViewPort(0, 3) = 250.0;
	mViewPort(1, 3) = 250.0;
	mViewPort(2, 2) = 1.0;
	mViewPort(3, 3) = 1.0;
}

void SetMatrix()
{
	static float angle = 0.0;
	angle += 0.01;
	mModelView.setIdentity();
	mProjection.setIdentity();

	myLookAt(0, 0, 0, 0, 0.2, -1, 0, 1, 0);
	myTranslate(0.0, 0.0, -6);
	//myRotateX(angle);
	myRotateY(angle);
	//myRotateZ(angle);
	myTranslate(0.0, 0.0, 6);

	myFrustum(-1, 1, -1, 1, 1, 10);
	//myOrtho(-10, 5, -10, 5, 1, 10);
	//myPerspective( 45.0, 1, 1, 10);
}

void init(void)
{
	mModelView.setIdentity();
	mProjection.setIdentity();
	mViewPort.setIdentity();

	glClearColor(0.949, 0.949, 0.949, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetMatrix();

	vector<vector<Eigen::Vector3f> > tris;

	vector<Eigen::Vector3f> tri1(3);
	tri1[0] = Eigen::Vector3f(4.0, 0, -6.000);
	tri1[1] = Eigen::Vector3f(-2.0, 3.0, -6.000);
	tri1[2] = Eigen::Vector3f(-2.0, -3.0, -6.000);

	vector<Eigen::Vector3f> tri2(3);
	tri2[0] = Eigen::Vector3f(3.0, 0, -4.000);
	tri2[1] = Eigen::Vector3f(-1.0, 1.0, -4.000);
	tri2[2] = Eigen::Vector3f(-1.0, -1.0, -4.000);

	tris.push_back(tri1);
	tris.push_back(tri2);

	vector<Eigen::Vector3f> tri_trans;

	for (int i = 0; i < tris.size(); ++i)
	{
		tri_trans = VertexTransform(tris[i]);

		glBegin(GL_TRIANGLES);
		glColor3ub(226, 86, 97);
		glVertex3fv(tri_trans[0].data());

		glColor3ub(214, 167, 201);
		glVertex3fv(tri_trans[1].data());

		glColor3ub(87, 150, 204);
		glVertex3fv(tri_trans[2].data());
		glEnd();
	}

	glFlush();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	WinSizeW = w;
	WinSizeH = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	myViewPort(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//这里near和far写反，是对的！
	//因为有一步z的取反已经在我们自己算坐标的过程中做了
	//此处不必追究,在这里是做特殊处理。
	//以后在自己写的代码中，依然要写成 glOrtho(0, w, 0.0, h, -1.0, 1.0);
	glOrtho(0, w, 0.0, h, 1.0, -1.0);

	//以下语句设置相机和物体的相对方位
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	Test();
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}



