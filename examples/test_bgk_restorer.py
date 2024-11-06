import matplotlib.pyplot as plt
import numpy as np
from bgk_restorer import fill_elevation

# Create sample data
dem = np.random.rand(100, 100).astype(np.float64)
count_map = np.ones_like(dem)
# Randomly set some pixels to 0
random_mask = np.random.random(dem.shape) < 0.8  # 60% of pixels will be 0
count_map[random_mask] = 0
dem[random_mask] = np.inf

# Set parameters
dist_threshold = 50.0
small_k_size = 3
large_k_size = 5
resolution = 0.05

# Execute elevation interpolation
filled_dem = fill_elevation(
    dem, count_map, small_k_size, large_k_size, resolution
)

plt.figure(figsize=(15, 5))

# Display original DEM
plt.subplot(131)
plt.imshow(dem)
plt.colorbar()
plt.title("Original DEM")

# Display count map
plt.subplot(132)
plt.imshow(count_map, cmap="gray")
plt.colorbar()
plt.title("Count Map")

# Display interpolated DEM
plt.subplot(133)
plt.imshow(filled_dem)
plt.colorbar()
plt.title("Filled DEM")

plt.tight_layout()
plt.show()
