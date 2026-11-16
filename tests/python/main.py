"""Проверка Python-модуля Kepler (запуск: python tests/python/main.py)."""
import math

import numpy as np

import Kepler

mu = 398600.4418  # км^3/с^2


def specific_energy(state):
    return 0.5 * state.v @ state.v - mu / np.linalg.norm(state.r)


def test_round_trip():
    kep = Kepler.KeplerElements(
        a=10000.0, e=0.3,
        i=math.radians(45.0),
        RAAN=math.radians(60.0),
        w=math.radians(30.0),
        nu=math.radians(10.0),
    )
    state = Kepler.KeplerToRV(kep, mu)
    result = Kepler.RVToKepler(state, mu)

    assert abs(result.a / kep.a - 1.0) < 1e-9
    assert abs(result.e - kep.e) < 1e-9
    assert abs(result.i - kep.i) < 1e-9
    assert abs(result.RAAN - kep.RAAN) < 1e-9
    assert abs(result.w - kep.w) < 1e-9
    assert abs(result.nu - kep.nu) < 1e-9


def test_kepler_equation():
    M, e = 1.2, 0.4
    E = Kepler.MeanToEccentricAnomaly(M, e)
    assert abs(E - e * math.sin(E) - M) < 1e-10


def test_circular_quarter_period():
    a = 7000.0
    v_circ = math.sqrt(mu / a)
    T = 2.0 * math.pi * math.sqrt(a**3 / mu)
    state0 = Kepler.Cartesian(r=np.array([a, 0.0, 0.0]), v=np.array([0.0, v_circ, 0.0]))

    state = Kepler.OrbitalPrediction(state0, 0.0, T / 4.0, mu)

    assert np.allclose(state.r, [0.0, a, 0.0], atol=1e-6)
    assert np.allclose(state.v, [-v_circ, 0.0, 0.0], atol=1e-9)


def test_conservation():
    kep = Kepler.KeplerElements(10000.0, 0.3, 0.8, 1.0, 0.5, 0.0)
    state0 = Kepler.KeplerToRV(kep, mu)
    energy0 = specific_energy(state0)
    h0 = np.cross(state0.r, state0.v)
    T = 2.0 * math.pi * math.sqrt(kep.a**3 / mu)

    for t in np.linspace(0.0, 3.0 * T, 200):
        state = Kepler.OrbitalPrediction(state0, 0.0, float(t), mu)
        dE = abs(specific_energy(state) - energy0) / abs(energy0)
        h = np.cross(state.r, state.v)
        dh = np.linalg.norm(h - h0) / np.linalg.norm(h0)
        assert dE < 1e-12, f"energy drift {dE:.2e} at t={t}"
        assert dh < 1e-12, f"h drift {dh:.2e} at t={t}"


if __name__ == "__main__":
    test_round_trip()
    test_kepler_equation()
    test_circular_quarter_period()
    test_conservation()
    print("Kepler: all checks passed")