#pragma once
#include "ray.hpp"
#include "scene.hpp"
#include <iostream>
#define MAXDEPTH 20
const float pi = 3.1415926;

bool Refract(const Vector3f& d, const Vector3f& n,
	float ni_over_nt, Vector3f& refracted)
{
	Vector3f unit_d = d.normalized();
	float dt = unit_d.dot(n);
	float disc = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
	if (disc > 0)
	{
		refracted = ni_over_nt * (unit_d - n * dt) - n * sqrt(disc);
	}
	else
		return false;
}


Vector3f RayColor(const Ray& ray, Scene& scene, int depth=0, bool test=false)
{
	HitInfo closest_hp;
	closest_hp.t = FLT_MAX;
	closest_hp.objIdx = -1;
	//光线和球求交
	for (int i = 0; i < scene.ObjectCount(); ++i)
	{
		HitInfo ht;
		bool bhit = scene.GetObjectPtr(i)->Hit(ray, ht);
		if (bhit)
		{
			if (ht.t > 0 && ht.t<closest_hp.t)
			{
				closest_hp = ht;
				closest_hp.objIdx = i;
			}
		}
	}

	//这里图省事，直接把光照参数写在这边

	vector<Vector3f> lightpos;
	Vector3f lightAmbient(0.6, 0.6, 0.6);
	Vector3f lightDiffuse(1.0, 1.0, 1.0);
	Vector3f lightSpecular(1.0, 1.0, 1.0);
	int t = 3;
	Vector3f center(0.0, 4, 2);
	float R = 0.1f;
	float delta = 2 * pi / t;
	float dr = R / t;
	for (int i = 0;i < t;i++)
	{
		for (int j = 0;j < t;j++)
		{
			float x = R * cos(delta * i) * sin(delta * j);
			float y = R * sin(delta * i) * sin(delta * j);
			float z = R * cos(delta * j);
			Vector3f p = center + Vector3f(x, y, z);
			lightpos.push_back(p);
		}
	}

	int n = lightpos.size();
	int cnt = 0;
	if (closest_hp.objIdx != -1)
	{
		int idx = closest_hp.objIdx;
		Material mtl = scene._scene[idx].second;
		//环境光
		Vector3f ambient = Vector3f(lightAmbient[0]* mtl._Ka[0],
			lightAmbient[1] * mtl._Ka[1], lightAmbient[2] * mtl._Ka[2]);

		Vector3f color = ambient;
		bool isShadow = false;
		Vector3f eyedir = (Vector3f(0, 0, 0) - closest_hp.position).normalized();
		//shadow ray 求交
		for (int j = 0;j < n;++j)
		{
			Ray shadow_ray(closest_hp.position, lightpos[j] - closest_hp.position);

			//请在以下部分加入对shadow ray是否被场景遮挡的判断，并对isShadow这个变量进行修改 

			//epsilon
			for (int i = 0; i < scene.ObjectCount(); ++i)
			{
				HitInfo ht;
				bool is_hit = scene.GetObjectPtr(i)->Hit(shadow_ray, ht);
				if (is_hit) isShadow = true;
			}
			//请在以上部分加入对shadow ray是否被场景遮挡的判断，并对isShadow这个变量进行修改 

			if (!isShadow)  //如果不是阴影，继续计算
			{
				//漫反射
				Vector3f lightdir = (lightpos[j] - closest_hp.position).normalized();
				float coscoef = lightdir.dot(closest_hp.normal);
				if (coscoef < 0) coscoef = 0;
				Vector3f diffuse = Vector3f(0.8 * mtl._Kd[0] * coscoef,
					0.8 * mtl._Kd[1] * coscoef,
					0.8 * mtl._Kd[2] * coscoef);

				Vector3f half = (eyedir + shadow_ray.Direction().normalized()).normalized();
				float specularcoef = half.dot(closest_hp.normal);
				if (specularcoef < 0) specularcoef = 0;
				else specularcoef = pow(specularcoef, mtl._shiness);
				Vector3f specular = Vector3f(lightSpecular[0] * mtl._Ks[0] * specularcoef,
					lightSpecular[1] * mtl._Ks[1] * specularcoef,
					lightSpecular[2] * mtl._Ks[2] * specularcoef);

				color += 1.0/n*diffuse + 1.0 / n * specular;
			}
		}
		
		Vector3f reflectColor(0.0, 0.0, 0.0);
		Vector3f reflectDir = 2.0*eyedir.dot(closest_hp.normal)*closest_hp.normal - eyedir;
		Ray reflectRay(closest_hp.position, reflectDir);
		reflectRay._origin = closest_hp.position + 1e-2*reflectDir.normalized();
		if (mtl._reflective)
		{
			//镜面光，调用递归

			//请以下部分，填入正确的递归调用
			if (depth <= MAXDEPTH)
			{
				reflectColor = RayColor(reflectRay, scene, depth+1, test);
			}

			//请以上部分，填入正确的递归调用
		}

		//折射，调用递归
		Vector3f refractionColor(0.0, 0.0, 0.0);
		if (mtl._transparent)
		{
			/*printf("_transparent");
			getchar();*/
			//折射光，调用递归
			Vector3f refractDir;
			float ni_over_nt;
			bool refract;
			if (ray.Direction().dot(closest_hp.normal) < 0) //入射
			{
				ni_over_nt = 1.0 / mtl._refraction;
				refract = Refract(ray.Direction(), closest_hp.normal, ni_over_nt, refractDir);
			}
			else//出射
			{
				ni_over_nt = mtl._refraction;
				refract = Refract(ray.Direction(), -closest_hp.normal, ni_over_nt, refractDir);
			}
			
			if (refract)
			{
				Ray refractRay(closest_hp.position, refractDir);
				refractRay._origin = closest_hp.position + 1e-2*refractDir.normalized();
				
				//请把下面代码改掉，填入正确的递归调用

				if(depth<MAXDEPTH) refractionColor =RayColor(refractRay, scene, depth, test);
				
				//请把上面代码改掉，填入正确的递归调用
			}
			else
			{
				refractionColor = Vector3f(0, 0, 0);
			}

			//cout << "refractionColor" << refractionColor << endl;
		}

		color = color + 0.2*reflectColor + 0.9*refractionColor;
		if (color[0] > 1.0) color[0] = 1.0;
		if (color[1] > 1.0) color[1] = 1.0;
		if (color[2] > 1.0) color[2] = 1.0;
		return color;
	}

	return Vector3f(0.6, 0.8, 0.8);
	//return Vector3f(1.0, 1.0, 1.0);
}