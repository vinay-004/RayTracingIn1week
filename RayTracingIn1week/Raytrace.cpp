#pragma once

#include<iostream>
#include<fstream>
#include<float.h>
#include"Camera.h"
#include"Hitable.h"
#include"material.h"


Vec3 Color(const Ray& r, Hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation*Color(scattered, world, depth + 1);
		}
		else {
			return Vec3(0, 0, 0);
		}
	}
	else {
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	int nx = 400;
	int ny = 200;
	int ns = 100;
	Camera cam;
	std::ofstream myfile("basic.ppm");

	if(myfile.is_open())
	{
		myfile << "P3\n" << nx << " " << ny <<"\n255"<< std::endl;
			
		

		Hitable *list[4];
		list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new lambertian(Vec3(0.1, 0.2, 0.5)));
		list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new lambertian(Vec3(0.8, 0.8, 0.0)));
		list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new metal(Vec3(0.8, 0.6, 0.2), 0.0));
		list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new metal(Vec3(0.8, 0.8, 0.8), 0.0));
		Hitable *world = new HitableList(list, 4);

		for (int  j = ny-1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				Vec3 color =  Vec3(0.0, 0.0, 0.0);
				for (int s = 0; s < ns; s++)
				{


					float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(nx);
					float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(ny);

					Ray ray = cam.get_ray(u, v);
					color += Color(ray, world,0);
				}
				color /= float(ns);
				int ir = int(255.99 * sqrt(color.r()));
				int ig = int(255.99 * (color.g()));
				int ib = int(255.99 * sqrt(color.b()));
			
				myfile<< ir << " " << ig << " " << ib << std::endl;
				//std::cout << ir << " " << ig << " " << ib <<std::endl;
			}
		}

	}
	return 0;
}