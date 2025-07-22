#pragma once
#include <Eigen/Core>
#include "ray.hpp"
#include  <vector>
using namespace std;
using namespace Eigen;

struct HitInfo
{
	float t;
	float t1, t2;
	Vector3f position;
	Vector3f normal;
	bool hit;
	int objIdx;
};

class Material
{
public:
	Material() {
		_transparent = false;
		_reflective = false;
	}

	void SetKa(Vector3f ka) {
		_Ka = ka;
	}

	void SetKd(Vector3f kd) {
		_Kd = kd;
	}

	void SetKs(Vector3f ks) {
		_Ks = ks;
	}

	void SetKm(Vector3f km) {
		_Km = km;
	}

	void SetShiness(float sh) {
		_shiness = sh;
	}

	void SetTransparent(bool trans)
	{
		_transparent = trans;
	}

	void SetRefraction(float refra)
	{
		_refraction = refra;
	}

	void SetReflective(bool reflective)
	{
		_reflective = reflective;
	}

	Vector3f _Ka;
	Vector3f _Kd;
	Vector3f _Ks;
	Vector3f _Km;//mirror
	float _shiness;
	float _refraction;//折射率
	bool _transparent;
	bool _reflective;
};

class Sphere
{
public:
	Sphere(const Vector3f& center, float r){
		_center = center;
		_r = r;
	}

	bool Hit(const Ray& ray, HitInfo& hinfo)
	{
		Vector3f oc = ray.Origin() - _center;
		float a = ray.Direction().dot(ray.Direction());
		float b = oc.dot(ray.Direction());
		float c = oc.dot(oc) - _r * _r;
		float disc = b * b - a * c;
		if (disc > 0) {
			float t1 = (-b - sqrt(b*b - a * c)) / a;
			float t2 = (-b + sqrt(b*b - a * c)) / a;
			hinfo.t1 = t1;
			hinfo.t2 = t2;

			if (t1 <= 1e-3 && t2 <= 1e-3)
				return false;
			if (t1 <= 1e-3 && t2 > 1e-3)
			{//从内部射出，取t2
				hinfo.hit = true;
				hinfo.t = t2;
				hinfo.position = ray.PointAtT(t2);
				hinfo.normal = (hinfo.position - _center).normalized();
				return true;
			}

			//t1 > 0, 从外部射入，取t1
			hinfo.hit = true;
			hinfo.t = t1;
			hinfo.position = ray.PointAtT(t1);
			hinfo.normal = (hinfo.position - _center).normalized();
			return true;
		}

		hinfo.hit = false;
		return false;
	}

	Vector3f _center;
	float _r;
};


class Scene
{
public:
	int ObjectCount() const{
		return _scene.size();
	}
	Sphere* GetObjectPtr(int i)
	{
		return &_scene[i].first;
	}

	void Insert(const pair<Sphere, Material>& obj){
		_scene.push_back(obj);
	}

	vector<pair<Sphere, Material> > _scene;
};