#include "dielectric.h"
#include "hittable.h"
#include "utility.h"
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

    auto unit_direction = ray.Direction().Unit();
    double cos_theta = std::fmin(unit_direction.dot(record.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    Vector3d direction;
    if (cannot_refract || Reflectance(cos_theta, ri) > Utility::random_double())
    {
        // Must reflect
        direction = Vector3d::Reflect(unit_direction, record.normal);
    }
    else 
    {
        // Can refract
        direction = Vector3d::Refract(unit_direction, record.normal, ri);
    }


    scattered = Ray(record.point, direction);
    return true;
}

}
