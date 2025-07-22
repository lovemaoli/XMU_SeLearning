#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;


void Test()
{
	//矩阵用法
	Eigen::Matrix4f m;
	cout << "Matrix:" << endl;
	cout << mViewPort << endl;

	//向量用法
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	//v[4] = 1.0;
	v.normalize();//归一化

	//输出矩阵与向量相乘的结果
	cout << "result:" << endl;
	cout << m * v << endl;
}

vector<Eigen::Vector3f> VertexTransform(vector<Eigen::Vector3f> vertices)
{
	vector<Eigen::Vector3f> rlt(vertices.size());
	Eigen::Vector4f v;

	Eigen::Matrix4f M = mViewPort * mProjection * mModelView;

	for (int i = 0; i < vertices.size(); ++i)
	{
		v[3] = 1.0;
		v.head<3>() = vertices[i];

		v = M * v;
		rlt[i][0] = v[0] / v[3];
		rlt[i][1] = v[1] / v[3];
		rlt[i][2] = v[2] / v[3];
	}
	return rlt;
}

Eigen::Matrix4f myLookAt(float ex, float ey, float ez, float atx, float aty, float atz, float upx, float upy, float upz)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数	
	Eigen::Vector3f e(ex, ey, ez);
	Eigen::Vector3f at(atx, aty, atz);
	Eigen::Vector3f t(upx, upy, upz);

	Eigen::Vector3f w = (e-at).normalized();
	Eigen::Vector3f u = (t.cross(w)).normalized();
	Eigen::Vector3f v = w.cross(u);

	Eigen::Matrix4f R;
	R<< u[0], u[1], u[2], 0,
		v[0], v[1], v[2], 0,
		w[0], w[1], w[2], 0,
		   0,    0,    0, 1;
	Eigen::Matrix4f T;
	T << 1, 0, 0, -ex,
		 0, 1, 0, -ey,
		 0, 0, 1, -ez,
		 0, 0, 0, 1;
	m = R * T;

	//请在上面空白处完成此函数
	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面粘贴上次实验的代码

	m << 1, 0, 0, 0,
		0, cos(theta), -sin(theta), 0,
		0, sin(theta), cos(theta), 0,
		0, 0, 0, 1;


	//请在上面粘贴上次实验的代码

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面粘贴上次实验的代码

	m << cos(theta), 0, sin(theta), 0,
		0, 1, 0, 0,
		-sin(theta), 0, cos(theta), 0,
		0, 0, 0, 1;


	//请在上面粘贴上次实验的代码

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面粘贴上次实验的代码

	m << cos(theta), -sin(theta), 0, 0,
		sin(theta), cos(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;


	//请在上面粘贴上次实验的代码

	mModelView *= m;
	return m;
}


Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面粘贴上次实验的代码

	m << 1, 0, 0, x,
		 0, 1, 0, y,
		 0, 0, 1, z,
		 0, 0, 0, 1;

	//请在上面粘贴上次实验的代码

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;

	//请在下面粘贴上次实验的代码

	float d = sqrt(x * x + y * y + z * z);

	float rx = x / d, ry = y / d, rz = z / d;

	m <<
		cos(theta) + (1 - cos(theta)) * rx * rx, (1 - cos(theta))* rx* ry - rz * sin(theta), (1 - cos(theta))* rx* rz + ry * sin(theta), 0,
		(1 - cos(theta))* rx* ry + rz * sin(theta), cos(theta) + (1 - cos(theta)) * ry * ry, (1 - cos(theta))* rz* ry - rx * sin(theta), 0,
		(1 - cos(theta))* rx* rz - ry * sin(theta), (1 - cos(theta))* rz* ry + rx * sin(theta), cos(theta) + (1 - cos(theta)) * rz * rz, 0,
		0;

	//请在上面粘贴上次实验的代码

	mModelView *= m;

	return m;
}

Eigen::Matrix4f myFrustum(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数
	
	m(0, 0) = 2 * n / (r - l);
	m(1, 1) = 2 * n / (t - b);
	m(2, 2) = -(f + n) / (f - n);
	m(0, 2) = (r + l) / (r - l);
	m(1, 2) = (t + b) / (t - b);
	m(3, 2) = -1;
	m(2, 3) = -2*f*n/(f-n);

	//请在上面空白处完成此函数

	mProjection *= m;
	return m;
}

Eigen::Matrix4f myOrtho(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数
	m(0, 0) = 2 / (r - l);
	m(0, 3) = -(r + l) / (r - l);
	m(1, 1) = 2 / (t - b);
	m(1, 3) = -(t + b) /(t - b);
	m(2, 2) = -2 / (f - n);
	m(2, 3) = -(f + n) / (f - n);
	m(3, 3) = 1;

	//请在上面空白处完成此函数

	mProjection *= m;

	return m;
}

Eigen::Matrix4f myViewPort(float x, float y, float w, float h)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数
	float Wheight = glutGet(GLUT_WINDOW_HEIGHT);
	m(0, 0) = w / 2;
	m(1, 1) = -h / 2;
	m(2, 2) = 1.0 / 2;
	m(3, 3) = 1.0;
	m(0, 3) = x + w / 2;
	m(1, 3) = Wheight-y - h / 2;
	m(2, 3) = 1.0 / 2;


	//请在上面空白处完成此函数

	mViewPort = m;

	return m;
}

Eigen::Matrix4f myPerspective(float fovy, float aspect, float zNear, float zFar)
{
	Eigen::Matrix4f m;
	m.setZero();
	const float pi = 3.1415926535897932384626433832795;

	m(0, 0) = -1 / (aspect * tan(fovy*pi/180/2));
	m(1, 1) = -1 / tan(fovy * pi / 180 / 2);
	m(2, 2) = (zFar + zNear) / (zFar - zNear);
	m(2, 3) = (2 * zFar * zNear) / (zFar - zNear);
	m(3, 2) = 1;

	mProjection *= m;
	return m;
}