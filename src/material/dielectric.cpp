#include "dielectric.h"
#include "hittable.h"
#include "vector3d.h"


namespace RayTracer
{


bool Dielectric::Scatter(const Ray& ray,
                         const Hittable::HitRecord &record,
                         RGB& attenuation,
                         Ray& scattered) const 
{
    attenuation = RGB{1, 1, 1};
    double ri = record.front_face ? (1.0 / m_refraction_index) : m_refraction_index;

    Vector3d refracted = Vector3d::Refract(
        ray.Direction().Unit(), 
        record.normal,
        ri
    );

    scattered = Ray(record.point, refracted);
    return true;
}

}
