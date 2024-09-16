#include "lambertian.h"
#include "hittable.h"
#include "vector3d.h"


namespace RayTracer
{


bool Lambertian::Scatter(const Ray& ray,
                         const Hittable::HitRecord &record,
                         RGB& attenuation,
                         Ray& scattered) const 
{
    // To remove unused warnings
    (void)ray;

    auto scatter_direction = record.normal + Vector3d::RandomUnitVector();
    if (scatter_direction.NearZero())
    {
        scatter_direction = record.normal;
    }

    scattered = Ray(record.point, scatter_direction);
    attenuation = m_albedo;
    return true;
}

}
