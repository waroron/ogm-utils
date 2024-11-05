import matplotlib.pyplot as plt
import numpy as np
from dem_creator import create_elevation_map


def main():
    # Create circular pattern points
    theta = np.linspace(0, 2 * np.pi, 100)
    radius = 0.5
    x = radius * np.cos(theta)
    y = radius * np.sin(theta)
    # Add sine wave variation to z
    z = 0.2 * np.sin(4 * theta) + 1.0

    points = np.column_stack([x, y, z])

    result = create_elevation_map(
        points=points,
        voxel_size=0.05,
        width=20,
        height=20,
        origin=(0.0, 0.0),
        include_stats=True,
        include_min_max=True,
    )

    # Visualization
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))

    # Plot elevation map
    im1 = axes[0, 0].imshow(result.elevation_map, origin="lower")
    axes[0, 0].set_title("Elevation Map")
    plt.colorbar(im1, ax=axes[0, 0])

    # Plot standard deviation map
    im2 = axes[0, 1].imshow(result.std_dev_map, origin="lower")
    axes[0, 1].set_title("Standard Deviation Map")
    plt.colorbar(im2, ax=axes[0, 1])

    # Plot point count map
    im3 = axes[1, 0].imshow(result.point_count_map, origin="lower")
    axes[1, 0].set_title("Point Count Map")
    plt.colorbar(im3, ax=axes[1, 0])

    # Plot 3D points
    ax3d = fig.add_subplot(2, 2, 4, projection="3d")
    ax3d.scatter(x, y, z, c=z, cmap="viridis")
    ax3d.set_title("Original Points")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
