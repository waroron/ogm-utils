#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "bgk_restorer.hpp"

namespace py = pybind11;

PYBIND11_MODULE(bgk_restorer, m) {
    m.doc() = "BGK restoration module"; // モジュールの説明

    m.def("fill_elevation", &fill_elevation<double>,
        py::arg("dem"),
        py::arg("count_map"),
        py::arg("dist_threshold"),
        py::arg("small_k_size"),
        py::arg("large_k_size"),
        py::arg("resolution"),
        "Fill elevation values using BGK filter");
}