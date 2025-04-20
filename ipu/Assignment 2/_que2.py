import numpy as np
import cv2
import matplotlib.pyplot as plt

# Load image and convert to suitable format
def load_image(path):
    img = cv2.imread(path)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    return img

# ---------- 1. K-MEANS from scratch ----------
def kmeans_segmentation(img, K=3, max_iters=10):
    Z = img.reshape((-1, 3)).astype(np.float32)
    np.random.seed(42)
    centers = Z[np.random.choice(len(Z), K, replace=False)]

    for _ in range(max_iters):
        distances = np.linalg.norm(Z[:, None] - centers[None, :], axis=2)
        labels = np.argmin(distances, axis=1)
        new_centers = np.array([Z[labels == i].mean(axis=0) if np.any(labels == i) else centers[i] for i in range(K)])
        if np.allclose(centers, new_centers):
            break
        centers = new_centers

    segmented = centers[labels].reshape(img.shape).astype(np.uint8)
    return segmented

# ---------- 2. Mean Shift (optimized with resizing) ----------
def mean_shift_segmentation(img, bandwidth=30, max_iters=10):
    # Resize image to speed up
    scale_percent = 30  # percent of original size
    width = int(img.shape[1] * scale_percent / 100)
    height = int(img.shape[0] * scale_percent / 100)
    resized_img = cv2.resize(img, (width, height), interpolation=cv2.INTER_LINEAR)

    flat_img = resized_img.reshape(-1, 3).astype(np.float32)
    shifted = np.copy(flat_img)

    print("Starting Mean Shift clustering...")
    for i in range(len(flat_img)):
        point = flat_img[i]
        for _ in range(max_iters):
            distances = np.linalg.norm(shifted - point, axis=1)
            neighbors = shifted[distances < bandwidth]
            if len(neighbors) == 0:
                break
            new_point = np.mean(neighbors, axis=0)
            if np.linalg.norm(new_point - point) < 1:
                break
            point = new_point
        shifted[i] = point

    unique_colors = np.unique(shifted.astype(int), axis=0)
    color_map = {tuple(c): i for i, c in enumerate(unique_colors)}
    labels = np.array([color_map[tuple(c.astype(int))] for c in shifted])
    mean_shift_img = unique_colors[labels].reshape(resized_img.shape).astype(np.uint8)

    # Resize back to original size
    mean_shift_img = cv2.resize(mean_shift_img, (img.shape[1], img.shape[0]), interpolation=cv2.INTER_NEAREST)
    return mean_shift_img

# ---------- 3. Otsu's Thresholding (manual) ----------
def otsu_threshold(img):
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    hist, _ = np.histogram(gray.flatten(), bins=256, range=(0, 256))
    total = gray.size
    sum_total = np.dot(np.arange(256), hist)

    sumB, wB, max_var, threshold = 0.0, 0, 0.0, 0
    for t in range(256):
        wB += hist[t]
        if wB == 0:
            continue
        wF = total - wB
        if wF == 0:
            break
        sumB += t * hist[t]
        mB = sumB / wB
        mF = (sum_total - sumB) / wF
        var_between = wB * wF * (mB - mF) ** 2
        if var_between > max_var:
            max_var = var_between
            threshold = t

    binary = (gray > threshold).astype(np.uint8) * 255
    return cv2.cvtColor(binary, cv2.COLOR_GRAY2RGB)

# ---------- Process and save results ----------
def process_image(image_path, title):
    print(f"\nProcessing: {title}")
    img = load_image(image_path)

    print("Running K-Means...")
    kmeans = kmeans_segmentation(img)

    print("Running Mean Shift...")
    mean_shift = mean_shift_segmentation(img)

    print("Running Otsu's Thresholding...")
    otsu = otsu_threshold(img)

    # Plot and save
    fig, axes = plt.subplots(1, 4, figsize=(16, 5))
    axes[0].imshow(img)
    axes[0].set_title("Original")
    axes[1].imshow(kmeans)
    axes[1].set_title("K-Means")
    axes[2].imshow(mean_shift)
    axes[2].set_title("Mean Shift")
    axes[3].imshow(otsu)
    axes[3].set_title("Otsu Threshold")
    for ax in axes:
        ax.axis("off")
    plt.suptitle(title)
    plt.tight_layout()

    save_name = title.replace(" ", "_").replace("-", "_") + ".png"
    plt.savefig(save_name)
    print(f"Saved: {save_name}")
    plt.close()

# -------- RUN ONLY FOR THESE TWO IMAGES --------
process_image("white-flower.png", "Segmentation White Flower")
process_image("butterfly.jpg", "Segmentation Butterfly")
