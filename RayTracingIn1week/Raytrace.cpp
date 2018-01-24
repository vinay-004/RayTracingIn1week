#include<iostream>
#include<fstream>
#include<float.h>
#include"Camera.h"

Vec3 random_in_unit_sphere()
{

	Vec3 p;

	do
	{
		float x = (rand() / (RAND_MAX + 1.0));
		float y = (rand() / (RAND_MAX + 1.0));
		float z = (rand() / (RAND_MAX + 1.0));
		p = 2.0 * Vec3(x, y, z) - Vec3(1.0, 1.0, 1.0);
	} while (dot(p,p) >= 1.0);						// point  on sphere is at a distance of radius from center of sphere

	return p;
}

Vec3 Color(const Ray &r, Hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		Vec3 target = rec.p + rec.normal + random_in_unit_sphere();

		return 0.5 * Color(Ray(rec.p, target - rec.p), world);
	}  
	else {

		Vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5 * (unit_dir.y() + 1.0);
		Vec3 col = (1.0 - t)* Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
		return col;

	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	Camera cam;
	std::ofstream myfile("basic.ppm");

	if(myfile.is_open())
	{
		myfile << "P3\n" << nx << " " << ny <<"\n255"<< std::endl;
			
		

		Hitable *list[2];
		list[0] = new Sphere(Vec3(0.0, 0.0, -1.0), 0.5 );
		list[1] = new Sphere(Vec3(0.0, -100.5, -1.0), 100.0);
		Hitable *world = new HitableList(list, 2);

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
					color += Color(ray, world);
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