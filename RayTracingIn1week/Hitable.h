#include<math.h>
#pragma once
#include"Ray.h"

// class Material;

struct hit_record
{
		float t;
		Vec3 p;
		Vec3 normal;
	//	Material *mat_rc;
};

class Hitable
{
public:
	virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &h) const = 0;
};

