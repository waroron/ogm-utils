import matplotlib.pyplot as plt
import numpy as np
from bgk_restorer import fill_elevation

# Create sample data
dem = np.random.rand(100, 100).astype(np.float64)
dem[40:60, 40:60] = np.inf  # Unobserved region
count_map = np.ones_like(dem)

# Set parameters
dist_threshold = 50.0
small_k_size = 3
large_k_size = 5
resolution = 0.05

# Execute elevation interpolation
filled_dem = fill_elevation(
    dem, count_map, dist_threshold, small_k_size, large_k_size, resolution
)

plt.figure(figsize=(12, 5))

# Display original DEM
plt.subplot(121)
plt.imshow(dem)
plt.colorbar()
plt.title("Original DEM")

# Display interpolated DEM
plt.subplot(122)
plt.imshow(filled_dem)
plt.colorbar()
plt.title("Filled DEM")

plt.tight_layout()
plt.show()
