#include "Anomalies.hpp"
#include <cmath>
#include <number>
#include <limits>

double TrueToEccentricAnomaly(double nu_0, double e) {
    return std::atan2(std::sin(nu_0) * std::sqrt(1.0 - e * e), e + std::cos(nu_0));
}

double EccentricToMeanAnomaly(double E_0, double e) {
    return E_0 - e * std::sin(E_0);
}

// прогноз средней аномалии М
double PropagateMeanAnomaly(double M0, double a, double mu, double t, double t0) {
    double n = std::sqrt(mu / a) / a;   // среднее движение
    return M0 + n * (t - t0);
}


double MeanToEccentricAnomaly(double M, double e, double tol, int maxIter) {
    constexpr double pi    = std::numbers::pi;
    constexpr double twoPi = 2.0 * std::numbers::pi;

    M = std::fmod(M, twoPi);
    if (M < 0) M += twoPi;                    

    double E = (M > pi) ? M - e : M + e;      
    for (int k = 0; k < maxIter; ++k) {
        double dE = (E - e * std::sin(E) - M) / (1.0 - e * std::cos(E));
        E -= dE;
       
    }
    return E;
}


double EccentricToTrueAnomaly(double E, double e) {
    return std::atan2(std::sin(E) * std::sqrt(1.0 - e * e), std::cos(E) - e);
}