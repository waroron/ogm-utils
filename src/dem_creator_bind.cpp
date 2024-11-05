#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "dem_creator.hpp"

namespace py = pybind11;

PYBIND11_MODULE(dem_creator, m) {
    m.doc() = "DEM creation module";

    py::class_<DEMResult>(m, "DEMResult")
        .def_readonly("elevation_map", &DEMResult::elevation_map)
        .def_readonly("std_dev_map", &DEMResult::std_dev_map)
        .def_readonly("point_count_map", &DEMResult::point_count_map)
        .def_readonly("min_map", &DEMResult::min_map)
        .def_readonly("max_map", &DEMResult::max_map);

    m.def("create_elevation_map", &create_elevation_map,
        py::arg("points"),
        py::arg("voxel_size"),
        py::arg("width"),
        py::arg("height"),
        py::arg("origin") = std::make_pair(0.0, 0.0),
        py::arg("include_stats") = false,
        py::arg("include_min_max") = false,
        "Create elevation map from point cloud data");
}
