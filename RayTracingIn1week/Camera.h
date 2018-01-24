#pragma once

#include"HitableList.h"

class Camera
{
public:
	Camera() 
	{
		 origin = Vec3(0.0, 0.0, 0.0);
		 vertical = Vec3(0.0, 2.0, 0.0);
		 horizontal = Vec3(4.0, 0.0, 0.0);
		 lower_left = Vec3(-2.0, -1.0, -1.0);
		
	};
	
	Ray get_ray(float u , float v)
	{
		Vec3 direction = lower_left + u * horizontal + v * vertical - origin;
		Ray ray(origin,direction);
		return ray;
	};

	Vec3 origin;
	Vec3 vertical;
	Vec3 horizontal;
	Vec3 lower_left;
};
