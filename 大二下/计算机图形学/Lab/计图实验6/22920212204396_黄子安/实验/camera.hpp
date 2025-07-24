#pragma once
#include "ray.hpp"
#include <Eigen/Core>
using namespace Eigen;

class Camera
{
public:
	Camera()
	{
		//注意：这里为了方便，直接把这几个参数写死了
		_origin = Vector3f(0, 0, 0);
		_lower_left_corner = Vector3f(-2.0, -1.5, -1.0);
		_horizontal = Vector3f(4.0, 0.0, 0.0);
		_vetical = Vector3f(0.0, 3.0, 0.0);
	}

	Ray GenerateRay(float u, float v)
	{
		//请改掉此函数，使得生成正确的光线
		return Ray(_origin,
			_lower_left_corner + u * _horizontal + v * _vetical - _origin);
	}

	Vector3f _origin;//相机中心
	Vector3f _lower_left_corner;//成像平面左下角
	Vector3f _horizontal;//成像平面的水平向量，注意这里不是归一化的向量，是从左下角指向左上角的向量
	Vector3f _vetical;//成像平面的竖直向量，注意这里不是归一化的向量，是从左下角指向右下角的向量
};