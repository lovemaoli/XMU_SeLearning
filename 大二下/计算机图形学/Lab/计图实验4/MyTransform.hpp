#pragma once

#include <Eigen/Core>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;

//此函数可随意改动
void Test()
{
	//关于eigen的用法，可参考：
	//http://eigen.tuxfamily.org/dox/group__QuickRefPage.html
	
	//矩阵用法
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//向量用法
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	v.normalize();//归一化

	//输出矩阵与向量相乘的结果
	cout << "result:" << endl;
	cout << m * v << endl;
}

//此函数不许改动
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

//绕x轴旋转angle角度
Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数


	m << 1, 0, 0, 0,
		0, cos(theta), -sin(theta), 0,
		0, sin(theta), cos(theta), 0,
		0, 0, 0, 1;




	//请在上面空白处完成此函数

	mModelView *= m;
	return m;
}

//绕y轴旋转angle角度
Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数

	m << cos(theta), 0, sin(theta), 0,
		0, 1, 0, 0,
		-sin(theta), 0, cos(theta), 0,
		0, 0, 0, 1;


	//请在上面空白处完成此函数

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//绕z轴旋转angle角度
Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数
	 
	m << cos(theta), -sin(theta), 0, 0,
		sin(theta), cos(theta), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;


	//请在上面空白处完成此函数

	mModelView *= m;
	//cout << m << endl;
	return m;
}


//平移x、y、z
Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数
	
	m << 1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1;


	//请在上面空白处完成此函数

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//绕轴(x,y,z)(注意:可能未归一化） 旋转angle角度
Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;
	
	//请在下面空白处完成此函数

	float d = sqrt(x * x + y * y + z * z);

	float Fai1 = acos(z/sqrt(z*z+y*y));
	if (y < 0) Fai1 = -Fai1;
	float Fai2=PI/2- acos(x / d);
	m = myRotateX(-Fai1*180/PI) * myRotateY(-Fai2 * 180 / PI) * myRotateZ(angle) * myRotateY(Fai2 * 180 / PI) * myRotateX(Fai1 * 180 / PI);

	//请在上面空白处完成此函数
	//cout << m;
	mModelView *= m;

	return m;
}

//沿x,y,z的缩放倍数
Eigen::Matrix4f myScalef( float x, float y, float z)
{

	Eigen::Matrix4f m;
	
	//请在下面空白处完成此函数

	m.setIdentity();//这句应该去掉




	//请在上面空白处完成此函数

	mModelView *= m;

	return m;
}

