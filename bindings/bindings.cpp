#include <nanobind/eigen/dense.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <iomanip>
#include <sstream>
#include <string>

#include "Anomalies.hpp"
#include "KeplerovToRV.hpp"
#include "OrbitalCoordinates.hpp"
#include "OrbitalPrediction.hpp"
#include "RVToKeplerov.hpp"

namespace nb = nanobind;
using namespace nb::literals;

namespace {

std::string FormatKeplerovElements(const KeplerovElements& k) {
    std::ostringstream out;
    out << std::setprecision(12)
        << "KeplerovElements(a=" << k.a << ", e=" << k.e << ", i=" << k.i
        << ", RAAN=" << k.RAAN << ", w=" << k.w << ", nu=" << k.nu << ")";
    return out.str();
}

std::string FormatCartesian(const Cartesian& s) {
    std::ostringstream out;
    out << std::setprecision(12)
        << "Cartesian(v=[" << s.v.x() << ", " << s.v.y() << ", " << s.v.z()
        << "], r=[" << s.r.x() << ", " << s.r.y() << ", " << s.r.z() << "])";
    return out.str();
}

}  // namespace

// Имя модуля = имя проекта в CMake (project(Kepler))
NB_MODULE(Kepler, m) {
    m.doc() = "Keplerov elements <-> Cartesian state and orbit prediction";

    // ------------------------------------------------------------------ типы
    nb::class_<KeplerovElements>(m, "KeplerovElements")
        .def(nb::init<>())
        .def("__init__",
             [](KeplerovElements* self, double a, double e, double i,
                double RAAN, double w, double nu) {
                 new (self) KeplerovElements{a, e, i, RAAN, w, nu};
             },
             "a"_a, "e"_a, "i"_a, "RAAN"_a, "w"_a, "nu"_a)
        .def_rw("a", &KeplerovElements::a)
        .def_rw("e", &KeplerovElements::e)
        .def_rw("i", &KeplerovElements::i)
        .def_rw("RAAN", &KeplerovElements::RAAN)
        .def_rw("w", &KeplerovElements::w)
        .def_rw("nu", &KeplerovElements::nu)
        .def("__repr__", &FormatKeplerovElements);

    // Порядок аргументов (v, r) такой же, как порядок полей в struct Cartesian.
    // Надёжнее вызывать по именам: Cartesian(r=..., v=...)
    nb::class_<Cartesian>(m, "Cartesian")
        .def(nb::init<>())
        .def("__init__",
             [](Cartesian* self, const Eigen::Vector3d& v, const Eigen::Vector3d& r) {
                 new (self) Cartesian();
                 self->v = v;
                 self->r = r;
             },
             "v"_a, "r"_a)
        .def_rw("v", &Cartesian::v)
        .def_rw("r", &Cartesian::r)
        .def("__repr__", &FormatCartesian);

    // ----------------------------------------------- функции (имена как в C++)
    m.def("KeplerovToRV", &KeplerovToRV, "kep"_a, "mu"_a);
    m.def("RVToKeplerov", &RVToKeplerov, "state"_a, "mu"_a);
    m.def("OrbitalPrediction", &OrbitalPrediction, "state0"_a, "t0"_a, "t"_a, "mu"_a);

    m.def("TrueToEccentricAnomaly", &TrueToEccentricAnomaly, "nu_0"_a, "e"_a);
    m.def("EccentricToMeanAnomaly", &EccentricToMeanAnomaly, "E_0"_a, "e"_a);
    m.def("PropagateMeanAnomaly", &PropagateMeanAnomaly,
          "M0"_a, "a"_a, "mu"_a, "t0"_a, "t"_a);
    m.def("MeanToEccentricAnomaly", &MeanToEccentricAnomaly,
          "M"_a, "e"_a, "tol"_a = 1e-12, "maxIter"_a = 50);
    m.def("EccentricToTrueAnomaly", &EccentricToTrueAnomaly, "E"_a, "e"_a);
}
