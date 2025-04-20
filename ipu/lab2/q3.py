import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load chessboard image
img_path = 'chessboard.png'  # Use your image path
img = cv2.imread(img_path)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# ---------- 1. Harris Corner Detection ----------
def harris_corners(gray_img, original_img, k=0.04, threshold=0.01):
    gray_float = np.float32(gray_img)
    dst = cv2.cornerHarris(gray_float, blockSize=2, ksize=3, k=k)

    dst = cv2.dilate(dst, None)  # Dilate for marking corners
    harris_img = original_img.copy()
    harris_img[dst > threshold * dst.max()] = [255, 0, 0]  # Mark corners in red
    return harris_img

# ---------- 2. SIFT Feature Detection ----------
def sift_features(gray_img, original_img):
    sift = cv2.SIFT_create()
    keypoints, descriptors = sift.detectAndCompute(gray_img, None)
    sift_img = cv2.drawKeypoints(original_img, keypoints, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    return sift_img

# Apply both detectors
harris_result = harris_corners(gray, img)
sift_result = sift_features(gray, img)

# Plot and Save Results
title = "Corner Detection - Chessboard"

plt.figure(figsize=(12, 5))
plt.suptitle(title, fontsize=16)

plt.subplot(1, 3, 1)
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.title('Original')
plt.axis('off')

plt.subplot(1, 3, 2)
plt.imshow(cv2.cvtColor(harris_result, cv2.COLOR_BGR2RGB))
plt.title('Harris Corners')
plt.axis('off')

plt.subplot(1, 3, 3)
plt.imshow(cv2.cvtColor(sift_result, cv2.COLOR_BGR2RGB))
plt.title('SIFT Features')
plt.axis('off')

plt.tight_layout()
plt.savefig(f"{title.replace(' ', '_')}.png")
print(f"Saved: {title.replace(' ', '_')}.png")
plt.close()
