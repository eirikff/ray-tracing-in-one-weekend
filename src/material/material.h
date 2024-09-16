#pragma once

#include "hittable.h"
#include "ray.h"
#include "color.h"


namespace RayTracer
{

class Material 
{
public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray& ray,
                         const Hittable::HitRecord &record,
                         RGB& attenuation,
                         Ray& scattered) const
    {
        // To remove unused warnings
        (void)ray;
        (void)record;
        (void)attenuation;
        (void)scattered;
        return false;
    }
};

}
