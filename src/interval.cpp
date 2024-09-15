#include "interval.h"

namespace RayTracer
{

const Interval Interval::Empty = Interval(-Constants::Infinity, Constants::Infinity);
const Interval Interval::Universe = Interval(-Constants::Infinity, Constants::Infinity);

}

