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
pip install git+https://github.com/waroron/dem-tools.git
```

## Usage

### DEM Creator
```python
import numpy as np
from dem_creator import create_elevation_map
Sample point cloud data (Nx3 array)
points = np.random.rand(1000, 3)
Create elevation map
result = create_elevation_map(
points=points,
voxel_size=0.1,
width=100,
height=100,
origin=(0.0, 0.0),
include_stats=True,
include_min_max=True
)
Access results
elevation_map = result.elevation_map
std_dev_map = result.std_dev_map
point_count_map = result.point_count_map
min_map = result.min_map
max_map = result.max_map
```

### BGK Restorer
```python
from bgk_restorer import fill_elevation
import numpy as np
Create or load DEM with missing values (inf)
dem = np.random.rand(100, 100)
dem[40:60, 40:60] = np.inf # Unobserved region
count_map = np.ones_like(dem)
Fill missing elevation values
filled_dem = fill_elevation(
dem=dem,
count_map=count_map,
dist_threshold=50.0,
small_k_size=3,
large_k_size=5,
resolution=0.05
)
```
