#include <nanobind/eigen/dense.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <iomanip>
#include <sstream>
#include <string>

#include "Anomalies.hpp"
#include "KeplerToRV.hpp"
#include "OrbitalCoordinates.hpp"
#include "OrbitalPrediction.hpp"
#include "RVToKepler.hpp"

namespace nb = nanobind;
using namespace nb::literals;

namespace {

std::string FormatKeplerElements(const KeplerElements& k) {
    std::ostringstream out;
    out << std::setprecision(12)
        << "KeplerElements(a=" << k.a << ", e=" << k.e << ", i=" << k.i
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
    m.doc() = "Kepler elements <-> Cartesian state and orbit prediction";

    // ------------------------------------------------------------------ типы
    nb::class_<KeplerElements>(m, "KeplerElements")
        .def(nb::init<>())
        .def("__init__",
             [](KeplerElements* self, double a, double e, double i,
                double RAAN, double w, double nu) {
                 new (self) KeplerElements{a, e, i, RAAN, w, nu};
             },
             "a"_a, "e"_a, "i"_a, "RAAN"_a, "w"_a, "nu"_a)
        .def_rw("a", &KeplerElements::a)
        .def_rw("e", &KeplerElements::e)
        .def_rw("i", &KeplerElements::i)
        .def_rw("RAAN", &KeplerElements::RAAN)
        .def_rw("w", &KeplerElements::w)
        .def_rw("nu", &KeplerElements::nu)
        .def("__repr__", &FormatKeplerElements);

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
    m.def("KeplerToRV", &KeplerToRV, "kep"_a, "mu"_a);
    m.def("RVToKepler", &RVToKepler, "state"_a, "mu"_a);
    m.def("OrbitalPrediction", &OrbitalPrediction, "state0"_a, "t0"_a, "t"_a, "mu"_a);

    m.def("TrueToEccentricAnomaly", &TrueToEccentricAnomaly, "nu_0"_a, "e"_a);
    m.def("EccentricToMeanAnomaly", &EccentricToMeanAnomaly, "E_0"_a, "e"_a);
    m.def("PropagateMeanAnomaly", &PropagateMeanAnomaly,
          "M0"_a, "a"_a, "mu"_a, "t0"_a, "t"_a);
    m.def("MeanToEccentricAnomaly", &MeanToEccentricAnomaly,
          "M"_a, "e"_a, "tol"_a = 1e-12, "maxIter"_a = 50);
    m.def("EccentricToTrueAnomaly", &EccentricToTrueAnomaly, "E"_a, "e"_a);
}
