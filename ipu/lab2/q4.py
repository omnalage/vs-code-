import cv2
import numpy as np
import matplotlib.pyplot as plt

# -------------- RGB to HSI Conversion Function ----------------
def rgb2hsi(rgb_img):
    rgb_img = rgb_img.astype('float32') / 255.0
    R, G, B = rgb_img[:, :, 0], rgb_img[:, :, 1], rgb_img[:, :, 2]

    # Intensity
    I = (R + G + B) / 3.0

    # Saturation
    min_rgb = np.minimum(np.minimum(R, G), B)
    S = 1 - (3 / (R + G + B + 1e-6)) * min_rgb  # Avoid division by zero

    # Hue calculation
    num = 0.5 * ((R - G) + (R - B))
    den = np.sqrt((R - G)**2 + (R - B)*(G - B)) + 1e-6
    theta = np.arccos(np.clip(num / den, -1, 1))  # Result in radians

    H = np.where(B <= G, theta, (2 * np.pi - theta))
    H = H / (2 * np.pi)  # Normalize H to range [0,1]

    return H, S, I

# -------------- Load Image ----------------
img = cv2.imread('camel.png')  # Ensure the file is in the same folder
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# -------------- Convert using Custom rgb2hsi ----------------
H_manual, S_manual, I_manual = rgb2hsi(img_rgb)

# -------------- Convert using OpenCV (HSV for comparison) ----------------
img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV).astype('float32')
H_cv = img_hsv[:, :, 0] / 179  # Normalize H to [0, 1]
S_cv = img_hsv[:, :, 1] / 255
I_cv = img_hsv[:, :, 2] / 255

# -------------- Compute Differences ----------------
diff_H = np.abs(H_manual - H_cv)
diff_S = np.abs(S_manual - S_cv)
diff_I = np.abs(I_manual - I_cv)

# -------------- Prepare Image Titles and Data ----------------
titles = [
    "Hue (Manual HSI)", "Saturation (Manual HSI)", "Intensity (Manual HSI)",
    "Hue (OpenCV HSV)", "Saturation (OpenCV HSV)", "Value (OpenCV HSV)",
    "Hue Difference", "Saturation Difference", "Intensity Difference"
]

images = [
    H_manual, S_manual, I_manual,
    H_cv, S_cv, I_cv,
    diff_H, diff_S, diff_I
]

# -------------- Display All in a Grid ----------------
fig, axes = plt.subplots(3, 3, figsize=(9, 7))  # Smaller figure size
fig.suptitle("HSI Conversion Results and Comparison", fontsize=14, y=1.02)

for i, ax in enumerate(axes.flat):
    ax.imshow(images[i], cmap='gray')
    ax.set_title(titles[i], fontsize=8)
    ax.axis('off')

plt.tight_layout(pad=1.5)
plt.show()
import cv2
import numpy as np
import matplotlib.pyplot as plt

# -------------- RGB to HSI Conversion Function ----------------
def rgb2hsi(rgb_img):
    rgb_img = rgb_img.astype('float32') / 255.0
    R, G, B = rgb_img[:, :, 0], rgb_img[:, :, 1], rgb_img[:, :, 2]

    # Intensity
    I = (R + G + B) / 3.0

    # Saturation
    min_rgb = np.minimum(np.minimum(R, G), B)
    S = 1 - (3 / (R + G + B + 1e-6)) * min_rgb  # Avoid division by zero

    # Hue calculation
    num = 0.5 * ((R - G) + (R - B))
    den = np.sqrt((R - G)**2 + (R - B)*(G - B)) + 1e-6
    theta = np.arccos(np.clip(num / den, -1, 1))  # Result in radians

    H = np.where(B <= G, theta, (2 * np.pi - theta))
    H = H / (2 * np.pi)  # Normalize H to range [0,1]

    return H, S, I

# -------------- Load Image ----------------
img = cv2.imread('camel.png')  # Ensure the file is in the same folder
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

# -------------- Convert using Custom rgb2hsi ----------------
H_manual, S_manual, I_manual = rgb2hsi(img_rgb)

# -------------- Convert using OpenCV (HSV for comparison) ----------------
img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV).astype('float32')
H_cv = img_hsv[:, :, 0] / 179  # Normalize H to [0, 1]
S_cv = img_hsv[:, :, 1] / 255
I_cv = img_hsv[:, :, 2] / 255

# -------------- Compute Differences ----------------
diff_H = np.abs(H_manual - H_cv)
diff_S = np.abs(S_manual - S_cv)
diff_I = np.abs(I_manual - I_cv)

# -------------- Prepare Image Titles and Data ----------------
titles = [
    "Hue (Manual HSI)", "Saturation (Manual HSI)", "Intensity (Manual HSI)",
    "Hue (OpenCV HSV)", "Saturation (OpenCV HSV)", "Value (OpenCV HSV)",
    "Hue Difference", "Saturation Difference", "Intensity Difference"
]

images = [
    H_manual, S_manual, I_manual,
    H_cv, S_cv, I_cv,
    diff_H, diff_S, diff_I
]

# -------------- Display and Save Each Figure Individually ----------------
for title, image in zip(titles, images):
    plt.figure(figsize=(4, 4))
    plt.imshow(image, cmap='gray')
    plt.title(title)
    plt.axis('off')
    plt.tight_layout()
    plt.savefig(f"{title.replace(' ', '_').replace('(', '').replace(')', '')}.png", bbox_inches='tight')
    print(f"Saved: {title.replace(' ', '_').replace('(', '').replace(')', '')}.png")
    plt.close()
