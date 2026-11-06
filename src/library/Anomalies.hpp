#pragma once

// ν -> E (t0)
double TrueToEccentricAnomaly(double nu_0, double e);

// E -> M (t0)
double EccentricToMeanAnomaly(double E_0, double e);

// M0 в момент t0 -> M в момент t
double PropagateMeanAnomaly(double M0, double a, double mu, double t0, double t);

// M -> E (метод Ньютона)
double MeanToEccentricAnomaly(double M, double e,
                              double tol = 1e-12, int maxIter = 50);

// E -> ν (t)
double EccentricToTrueAnomaly(double E, double e);