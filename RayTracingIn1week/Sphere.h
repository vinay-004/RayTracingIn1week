#pragma once
#include"Hitable.h"

class Sphere:public Hitable	
{
public:
	Sphere() {};
	Sphere(Vec3 origin, float r) : center(origin), radius(r) {};
	virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &h) const;

	float radius;
	Vec3 center;
	
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
			return true;
		}
		 temp = (-B + sqrt(discrimation)) / (A);
		if (temp > tmin && temp < tmax)
		{
			h.t = temp;
			h.p = r.point_at_parameter(h.t);
			h.normal = (h.p - center) / radius;
			return true;
		}
	}
	return false;
}
