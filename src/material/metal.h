#pragma once

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "ray.h"


namespace RayTracer
{

class Metal : public Material
{
public:
    Metal(const RGB& albedo, double fuzz) 
    : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1) 
    {}

    virtual bool Scatter(const Ray& ray,
                         const Hittable::HitRecord &record,
                         RGB& attenuation,
                         Ray& scattered) const override;

private:
    RGB m_albedo;
    double m_fuzz;
};

}
