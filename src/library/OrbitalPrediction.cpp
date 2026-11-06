#include "OrbitalPrediction.hpp"
#include "RVToKeplerov.hpp"
#include "KeplerovToRV.hpp"
#include "Anomalies.hpp"


Cartesian OrbitalPrediction(const Cartesian& state0,
    double t0, double t, double mu) {

    KeplerovElements kep = RVToKeplerov(state0, mu);

    const double E0 = TrueToEccentricAnomaly(kep.nu, kep.e);
    const double M0 = EccentricToMeanAnomaly(E0, kep.e);
    const double M = PropagateMeanAnomaly(M0, kep.a, mu, t0, t);
    const double E = MeanToEccentricAnomaly(M, kep.e);
    // а тут const нужен ?!
    kep.nu = EccentricToTrueAnomaly(E, kep.e);

    return KeplerovToRV(kep, mu);
}