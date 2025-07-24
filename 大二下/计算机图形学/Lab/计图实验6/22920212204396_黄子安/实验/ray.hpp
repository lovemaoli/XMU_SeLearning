#pragma once
#include <Eigen/Core>
using namespace Eigen;

class Ray
{
public:
	Ray(const Vector3f& origin, const Vector3f& direction){
		_origin = origin;
		_direction = direction;
	}

	Vector3f Origin() const { return _origin; }

	Vector3f Direction() const { return _direction; }

	Vector3f PointAtT(float t) const{
		return _origin + t * _direction;
	}

	Vector3f _origin;
	Vector3f _direction;
};