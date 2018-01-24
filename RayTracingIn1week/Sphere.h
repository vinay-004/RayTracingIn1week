#pragma once
#include"Hitable.h"

class Sphere:public Hitable	
{
public:
	Sphere() {};
	Sphere(Vec3 origin, float r,material *m) : center(origin), radius(r),mat_ptr(m) {};
	virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &h) const;

	float radius;
	Vec3 center;
	material *mat_ptr;
	
};

bool Sphere::hit(const Ray & r, float tmin, float tmax, hit_record & h) const
{
	Vec3 oc = r.origin() - center;
	float B = dot(oc,r.direction());
	float A = dot(r.B, r.B);
	float C = dot(oc, oc) - radius*radius;
	float discrimation = B*B -  A*C;

	if (discrimation > 0.0)
	{
		float temp = (-B - sqrt(discrimation)) / (A);
		if(temp > tmin && temp < tmax)
		{
			h.t = temp;
			h.p = r.point_at_parameter(h.t);
			h.normal = (h.p - center) / radius;
			h.mat_ptr = mat_ptr;
			return true;
		}
		 temp = (-B + sqrt(discrimation)) / (A);
		if (temp > tmin && temp < tmax)
		{
			h.t = temp;
			h.p = r.point_at_parameter(h.t);
			h.normal = (h.p - center) / radius;
			h.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
