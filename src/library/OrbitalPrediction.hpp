#pragma once
#include "OrbitalCoordinates.hpp"   // KeplerovElements, Cartesian

// (r0, v0) в момент t0 -> (r, v) в момент t
Cartesian OrbitalPrediction(const Cartesian& state0,
    double t0, double t, double mu);