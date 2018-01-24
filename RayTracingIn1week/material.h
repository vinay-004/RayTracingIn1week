


#include"Ray.h"
#include"Hitable.h"

struct hit_record;
Vec3 random_in_unit_sphere()
{

	Vec3 p;

	do
	{
		float x = (rand() / (RAND_MAX + 1.0));
		float y = (rand() / (RAND_MAX + 1.0));
		float z = (rand() / (RAND_MAX + 1.0));
		p = 2.0 * Vec3(x, y, z) - Vec3(1.0, 1.0, 1.0);
	} while (dot(p, p) >= 1.0);						// point  on sphere is at a distance of radius from center of sphere

	return p;
}

Vec3 reflect(const Vec3 &v , const Vec3 &n)
{
	return v - 2 * dot(v, n)*n;
}

class material
{
public:
	virtual bool scatter(const Ray &r, const hit_record &rec, Vec3 &attenuation, Ray & scattered) const = 0;
};

class lambertian : public material {
public:
	lambertian(const Vec3& a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
		Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}

	Vec3 albedo;
};

class metal : public material {
public:
	metal(const Vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
		Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	Vec3 albedo;
	float fuzz;
};


