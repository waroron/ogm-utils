# 結果の可視化
import matplotlib.pyplot as plt
import numpy as np
from bgk_restorer import fill_elevation

# サンプルデータの作成
dem = np.random.rand(100, 100).astype(np.float64)
dem[40:60, 40:60] = np.inf  # 未観測領域
count_map = np.ones_like(dem)

# パラメータ設定
dist_threshold = 50.0
small_k_size = 3
large_k_size = 5
resolution = 0.05

# 標高値の補完を実行
filled_dem = fill_elevation(
    dem, count_map, dist_threshold, small_k_size, large_k_size, resolution
)

plt.figure(figsize=(12, 5))

# オリジナルのDEMを表示
plt.subplot(121)
plt.imshow(dem)
plt.colorbar()
plt.title("Original DEM")

# 補完後のDEMを表示
plt.subplot(122)
plt.imshow(filled_dem)
plt.colorbar()
plt.title("Filled DEM")

plt.tight_layout()
plt.show()
