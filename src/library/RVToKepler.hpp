#pragma once
#include "OrbitalCoordinates.hpp"
KeplerElements RVToKepler(const Cartesian& state, const double mu);