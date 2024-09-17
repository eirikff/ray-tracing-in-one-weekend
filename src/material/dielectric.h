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

    static double Reflectance(double cos, double refraction_index)
    {
        // Using Schlick's approximation for reflectance
        double r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow(1.0 - cos, 5);
    }
};

}
