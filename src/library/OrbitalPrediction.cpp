#include "OrbitalPrediction.hpp"
#include "RVToKeplerov.hpp"
#include "KeplerovToRV.hpp"
#include "Anomalies.hpp"


Cartesian OrbitalPrediction(const Cartesian& state0,
    double t0, double t, double mu) {

    const KeplerovElements kep = RVToKeplerov(state0, mu);

    const double E0 = TrueToEccentricAnomaly(kep.nu, kep.e);
    const double M0 = EccentricToMeanAnomaly(E0, kep.e);
    const double M = PropagateMeanAnomaly(M0, kep.a, mu, t0, t);
    const double E = MeanToEccentricAnomaly(M, kep.e);
    nu = EccentricToTrueAnomaly(E, kep.e);

    return KeplerovToRV{ //создаем что-то типа копии (чтобы было видно, что изменилось)
        .a    = kep.a,
        .e    = kep.e,
        .i    = kep.i,
        .RAAN = kep.RAAN,
        .w    = kep.w,
        .nu   = nu
    };
}