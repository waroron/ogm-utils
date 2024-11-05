#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>

namespace py = pybind11;

template<typename T>
py::array_t<T> fill_elevation(
    py::array_t<T> dem,
    py::array_t<T> count_map,
    double dist_threshold,
    int small_k_size,
    int large_k_size,
    double resolution
) {
    // Get buffer information for input arrays
    auto dem_buf = dem.request();
    auto count_buf = count_map.request();
    
    if (dem_buf.ndim != 2) {
        throw std::runtime_error("Number of dimensions must be 2");
    }

    const int rows = dem_buf.shape[0];
    const int cols = dem_buf.shape[1];
    
    // Create output array
    auto pred_dem = py::array_t<T>({rows, cols});
    auto pred_buf = pred_dem.request();
    
    // Get data pointers
    T* dem_ptr = static_cast<T*>(dem_buf.ptr);
    T* count_ptr = static_cast<T*>(count_buf.ptr);
    T* pred_ptr = static_cast<T*>(pred_buf.ptr);
    
    // Copy input DEM
    std::memcpy(pred_ptr, dem_ptr, rows * cols * sizeof(T));
    
    // Apply BGK filter
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            const int idx = i * cols + j;
            
            // Determine kernel size
            int k_size = std::isinf(dem_ptr[idx]) ? large_k_size : small_k_size;
            int half_k = k_size / 2;
            
            // Calculate kernel range
            int i_start = std::max(0, i - half_k);
            int i_end = std::min(rows, i + half_k + 1);
            int j_start = std::max(0, j - half_k);
            int j_end = std::min(cols, j + half_k + 1);
            
            double sum_weights = 0.0;
            double sum_values = 0.0;
            bool has_valid = false;
            
            // Calculate weighted average of neighboring grids
            for (int ni = i_start; ni < i_end; ni++) {
                for (int nj = j_start; nj < j_end; nj++) {
                    const int n_idx = ni * cols + nj;
                    if (!std::isinf(dem_ptr[n_idx])) {
                        // Calculate distance weight
                        double dist = std::sqrt(
                            std::pow((ni - i) * resolution, 2) + 
                            std::pow((nj - j) * resolution, 2)
                        );
                        double weight = std::exp(-dist / dist_threshold);
                        
                        sum_weights += weight;
                        sum_values += weight * dem_ptr[n_idx];
                        has_valid = true;
                    }
                }
            }
            
            // Update only if valid neighboring grids exist
            if (has_valid) {
                pred_ptr[idx] = static_cast<T>(sum_values / sum_weights);
            }
        }
    }
    
    return pred_dem;
}