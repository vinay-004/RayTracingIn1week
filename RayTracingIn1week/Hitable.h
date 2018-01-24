#pragma once

#include<math.h>
#include"Ray.h"

 class material;

struct hit_record
{
		float t;
		Vec3 p;
		Vec3 normal;
		material *mat_ptr;
};

class Hitable
{
public:
	virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &h) const = 0;
};

