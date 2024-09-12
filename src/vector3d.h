#pragma once

#include <cmath>
#include <cstddef>
#include <array>
#include <cstdint>
#include <ostream>


namespace RayTracer 
{

class Vector3d;
using Point3d = Vector3d;

Vector3d Lerp(const Vector3d &a, const Vector3d &b, double t);

class Vector3d
{
public:
	Vector3d()
	: m_data{0, 0, 0}
	{ }

	Vector3d(double x, double y, double z)
	: m_data{x, y, z}
	{ }

	Vector3d(const Vector3d &other)
	: m_data{other.m_data}
	{ }

	const double &x() const { return m_data[0]; }
	const double &y() const { return m_data[1]; }
	const double &z() const { return m_data[2]; }

	const double &operator[](size_t i) const { return m_data[i]; }
	double &operator[](size_t i) { return m_data[i]; }

	Vector3d &operator=(const Vector3d &other)
	{
		if (this == &other)
			return *this;

		m_data = { other.x(), other.y(), other.z() };
		return *this;
	}
	Vector3d operator+(const Vector3d &other) const
	{
		Vector3d ret{ x() + other.x(), y() + other.y(), z() + other.z() };
		return ret;
	}
	Vector3d &operator+=(const Vector3d &other)
	{
		m_data[0] += other[0];
		m_data[1] += other[1];
		m_data[2] += other[2];
		return *this;
	}
	Vector3d operator-(void) const { return Vector3d{-x(), -y(), -z()}; }
	Vector3d operator-(const Vector3d &other) const 
	{ 
		return *this + (-other);
	}
	Vector3d &operator-=(const Vector3d &other)
	{
		m_data[0] -= other[0];
		m_data[1] -= other[1];
		m_data[2] -= other[2];
		return *this;
	}
	Vector3d operator*(double s) const
	{
		Vector3d ret{ x() * s, y() * s, z() * s };
		return ret;
	}
	friend Vector3d operator*(double s, const Vector3d &v) { return v * s; }
	Vector3d &operator*=(double s) 
	{
		m_data[0] *= s;
		m_data[1] *= s;
		m_data[2] *= s;
		return *this;
	}
	Vector3d operator/(double s) const
	{
		Vector3d ret{ x() / s, y() / s, z() / s };
		return ret;
	}
	Vector3d &operator/=(double s) 
	{
		m_data[0] /= s;
		m_data[1] /= s;
		m_data[2] /= s;
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const Vector3d &v)
	{
		os << "[" << v.x() << ", " << v.y() << ", " << v.z() << "]";
		return os;
	}

	double dot(const Vector3d &other) const
	{
		return x() * other.x() + y() * other.y() + z() * other.z();
	}
	Vector3d cross(const Vector3d &other) const
	{
		Vector3d ret{
			y() * other.z() - z() * other.y(),
			z() * other.x() - x() * other.z(),
			x() * other.y() - y() * other.x()
		};
		return ret;
	}

	double LengthSquared() const { return x()*x() + y()*y() + z()*z(); }
	double Length() const { return std::sqrt(LengthSquared()); }
	Vector3d Unit() const { return *this / Length(); }
	std::array<uint8_t, 3> Uint8() const 
	{
		auto u = Unit() * 255;
		return std::array<uint8_t, 3>{ 
			uint8_t(u.x()), uint8_t(u.y()), uint8_t(u.z())
		};
	}

protected:
	std::array<double, 3> m_data;
};

}
