#include "metal.h"
#include "hittable.h"
#include "vector3d.h"


namespace RayTracer
{


bool Metal::Scatter(const Ray& ray,
                    const Hittable::HitRecord &record,
                    RGB& attenuation,
                    Ray& scattered) const
{
    auto reflected = Vector3d::Reflect(ray.Direction(), record.normal);
    reflected = reflected.Unit() + (m_fuzz * Vector3d::RandomUnitVector());
    scattered = Ray(record.point, reflected);
    attenuation = m_albedo;
    return scattered.Direction().dot(record.normal) > 0;
}

}
