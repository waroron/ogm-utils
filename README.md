# DEM Creator and BGK Restorer

Digital Elevation Map (DEM) creation and restoration tools with Python bindings.

## Features

- **DEM Creator**: Creates elevation maps from point cloud data
  - Generates elevation maps with statistical information (std dev, point count)
  - Optional min/max elevation values for each cell
  - Configurable voxel size and map dimensions

- **BGK Restorer**: Fills missing elevation values in DEMs
  - Uses Bilateral Gaussian Kernel (BGK) filtering
  - Handles unobserved regions (marked as inf)
  - Configurable kernel sizes and distance threshold

## Requirements

- C++17 compatible compiler
- Python 3.7+
- pybind11
- numpy
- matplotlib (for examples)

## Installation

### From Source

1. Clone the repository:

```bash
git clone https://github.com/yourusername/dem-tools.git
cd dem-tools
```


2. Create and activate a virtual environment (optional but recommended):

```bash
python -m venv venv
source venv/bin/activate # Linux/Mac
or
.\venv\Scripts\activate # Windows
```

3. Install dependencies:

```bash
pip install numpy pybind11 matplotlib
```

4. Build and install:
```bash
pip install .
```

### Using pip (from GitHub)

```bash
pip install git+https://github.com/waroron/ogm-utils.git
```

## Usage

### DEM Creator
You can see the usage of DEM Creator in the [examples/test_dem_creator.py](examples/test_dem_creator.py) file.

### BGK Restorer
You can see the usage of BGK Restorer in the [examples/test_bgk_restorer.py](examples/test_bgk_restorer.py) file.
