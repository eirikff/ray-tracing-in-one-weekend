#pragma once

#include "utility.h"


namespace RayTracer
{

class Interval
{
public:
	Interval()
	: m_min(-Constants::Infinity), m_max(Constants::Infinity)
	{}
	Interval(double min, double max)
	: m_min(min), m_max(max)
	{}

	double Min() const { return m_min; }
	double Max() const { return m_max; }
	double &Min() { return m_min; }
	double &Max() { return m_max; }

	double Size() const { return m_max - m_min; }
	// Contains chekcs if the value is within the interval, including the 
	// lower and upper bounds
	bool Contains(double v) { return m_min <= v && v <= m_max; }
	// Surrounds only checks if the value is within the bounds, but not at the
	// bounds
	bool Surrounds(double v) { return m_min < v && v < m_max; }

	static const Interval Empty;
	static const Interval Universe;

private:
	double m_min;
	double m_max;
};

}
