#include "Anomalies.hpp"
#include <cmath>

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
    const double twoPi = 2.0 * M_PI;
    M = std::fmod(M, twoPi);
    if (M < 0) M += twoPi;                    // приводим M к [0, 2π)

    double E = (M > M_PI) ? M - e : M + e;    // начальное приближение (слайд 12)
    for (int k = 0; k < maxIter; ++k) {
        double dE = (E - e * std::sin(E) - M) / (1.0 - e * std::cos(E));
        E -= dE;
        if (std::abs(dE) < tol) break;
    }
    return E;
}

// Пункт 6: E -> ν
double EccentricToTrueAnomaly(double E, double e) {
    return std::atan2(std::sin(E) * std::sqrt(1.0 - e * e), std::cos(E) - e);
}