cmake_minimum_required(VERSION 3.10)
project(bgk_restorer)

# pybind11を見つける
find_package(pybind11 REQUIRED)

# C++17を使用
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ビルドターゲットを追加
pybind11_add_module(bgk_restorer src/bgk_restorer_bind.cpp)

# インクルードディレクトリを追加
target_include_directories(bgk_restorer PRIVATE include)