#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <vector>
#include <cmath>
#include <limits>
#include <tuple>

namespace py = pybind11;

struct DEMResult {
    py::array_t<double> elevation_map;
    py::array_t<double> std_dev_map;
    py::array_t<int> point_count_map;
    py::array_t<double> min_map;
    py::array_t<double> max_map;
};

DEMResult create_elevation_map(
    py::array_t<double> points,
    double voxel_size,
    int width,
    int height,
    std::pair<double, double> origin = std::make_pair(0.0, 0.0),
    bool include_stats = false,
    bool include_min_max = false
) {
    // 入力配列のバッファ情報を取得
    auto points_buf = points.request();
    if (points_buf.ndim != 2 || points_buf.shape[1] != 3) {
        throw std::runtime_error("Points must be Nx3 array");
    }

    // 出力配列を初期化
    auto elevation_map = py::array_t<double>({width, height});
    auto std_dev_map = py::array_t<double>({width, height});
    auto point_count_map = py::array_t<int>({width, height});
    auto min_map = py::array_t<double>({width, height});
    auto max_map = py::array_t<double>({width, height});

    // バッファを取得
    auto elev_buf = elevation_map.request();
    auto std_buf = std_dev_map.request();
    auto count_buf = point_count_map.request();
    auto min_buf = min_map.request();
    auto max_buf = max_map.request();

    // ポインタを取得
    double* elev_ptr = static_cast<double*>(elev_buf.ptr);
    double* std_ptr = static_cast<double*>(std_buf.ptr);
    int* count_ptr = static_cast<int*>(count_buf.ptr);
    double* min_ptr = static_cast<double*>(min_buf.ptr);
    double* max_ptr = static_cast<double*>(max_buf.ptr);

    // マップを初期化
    const double nan = std::numeric_limits<double>::quiet_NaN();
    for (size_t i = 0; i < width * height; ++i) {
        elev_ptr[i] = nan;
        std_ptr[i] = nan;
        count_ptr[i] = 0;
        min_ptr[i] = nan;
        max_ptr[i] = nan;
    }

    // 点群データを処理
    const double* points_ptr = static_cast<double*>(points_buf.ptr);
    const size_t n_points = points_buf.shape[0];

    // 統計情報用の一時的なストレージ
    std::vector<std::vector<std::vector<double>>> elevation_lists;
    if (include_stats || include_min_max) {
        elevation_lists.resize(width, std::vector<std::vector<double>>(height));
    }

    // 各点を処理
    for (size_t i = 0; i < n_points; ++i) {
        const double x = points_ptr[i * 3];
        const double y = points_ptr[i * 3 + 1];
        const double z = points_ptr[i * 3 + 2];

        // インデックスを計算
        int x_idx = static_cast<int>((x - origin.first) / voxel_size + width / 2);
        int y_idx = static_cast<int>((y - origin.second) / voxel_size + height / 2);

        // 範囲チェック
        if (x_idx >= 0 && x_idx < width && y_idx >= 0 && y_idx < height) {
            const size_t idx = x_idx * height + y_idx;

            if (include_stats || include_min_max) {
                elevation_lists[x_idx][y_idx].push_back(z);
            }

            if (std::isnan(elev_ptr[idx]) || z > elev_ptr[idx]) {
                elev_ptr[idx] = z;
            }
        }
    }

    // 統計情報を計算
    if (include_stats || include_min_max) {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                const size_t idx = x * height + y;
                const auto& points = elevation_lists[x][y];

                if (!points.empty()) {
                    if (include_stats) {
                        // 標準偏差を計算
                        double sum = 0.0, sum_sq = 0.0;
                        for (double z : points) {
                            sum += z;
                            sum_sq += z * z;
                        }
                        double mean = sum / points.size();
                        double variance = (sum_sq / points.size()) - (mean * mean);
                        std_ptr[idx] = std::sqrt(variance);
                        count_ptr[idx] = static_cast<int>(points.size());
                    }
                    if (include_min_max) {
                        // 最小値と最大値を計算
                        min_ptr[idx] = *std::min_element(points.begin(), points.end());
                        max_ptr[idx] = *std::max_element(points.begin(), points.end());
                    }
                }
            }
        }
    }

    return {
        elevation_map,
        std_dev_map,
        point_count_map,
        min_map,
        max_map
    };
}