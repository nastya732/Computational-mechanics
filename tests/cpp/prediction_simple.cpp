#include "OrbitalPrediction.hpp"
#include <cmath>
#include <iostream>

int main() {
    const double mu = 398600.4418;               // км^3/с^2

    Cartesian state0;
    state0.r = Eigen::Vector3d(7000.0, 0.0, 0.0);   // км
    state0.v = Eigen::Vector3d(0.0, 8.5, 2.0);      // км/с

    // большая полуось из энергии: v^2/2 - mu/r = -mu/(2a)
    double energy = state0.v.squaredNorm() / 2.0 - mu / state0.r.norm();
    double a = -mu / (2.0 * energy);
    double T = 2.0 * M_PI * std::sqrt(a * a * a / mu);   // период

    Cartesian state = OrbitalPrediction(state0, 0.0, T, mu);
    
    std::cout << state.r;
    std::cout << state.v;
    return 0;
}