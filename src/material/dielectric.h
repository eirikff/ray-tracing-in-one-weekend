#pragma once

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "ray.h"


namespace RayTracer
{

class Dielectric : public Material
{
public:
    Dielectric(double refraction_index) 
    : m_refraction_index(refraction_index) {}

    virtual bool Scatter(const Ray& ray,
                         const Hittable::HitRecord &record,
                         RGB& attenuation,
                         Ray& scattered) const override;

private:
    // Refractive index in vacuum or air, or the ratio of the material's 
    // refractive index over the refractive index of the enclosing media
    double m_refraction_index;
};

}
