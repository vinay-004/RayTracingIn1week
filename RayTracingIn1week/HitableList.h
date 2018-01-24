#pragma once
#include"Sphere.h"

class HitableList : public Hitable
{
public:
	HitableList() {};
	HitableList(Hitable **l, int n) { list = l; list_size = n; };
	
	virtual bool hit(const Ray &r, float tmin, float tmax, hit_record &h) const;

	Hitable**list;
	int list_size;
};

bool HitableList::hit(const Ray &r, float tmin, float tmax, hit_record &h) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = tmax;
	for (size_t i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, tmin, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			h = temp_rec;
		}
	}
	return hit_anything;
}