#pragma once

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "ray.h"


namespace RayTracer
{

class Lambertian : public Material
{
public:
    Lambertian(const RGB& albedo) : m_albedo(albedo) {}

    virtual bool Scatter(const Ray& ray,
                         const Hittable::HitRecord &record,
                         RGB& attenuation,
                         Ray& scattered) const override;

private:
    RGB m_albedo;
};

}
