import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load the image in grayscale
image = cv2.imread('morf_test.png', cv2.IMREAD_GRAYSCALE)

# Step 1: Use morphological operations to estimate background
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (25, 25))  # Adjust size based on noise/letters
background = cv2.morphologyEx(image, cv2.MORPH_CLOSE, kernel)  # Use closing to estimate background

# Step 2: Subtract background
subtracted = cv2.subtract(background, image)

# Optional: Top-hat or bottom-hat as alternative preprocessing
# top_hat = cv2.morphologyEx(image, cv2.MORPH_TOPHAT, kernel)
# bottom_hat = cv2.morphologyEx(image, cv2.MORPH_BLACKHAT, kernel)

# Step 3: Global thresholding
_, thresh = cv2.threshold(subtracted, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

# Step 4: Noise removal (optional)
cleaned = cv2.medianBlur(thresh, 3)  # or use morphological opening

# Step 5: Morphological operations to close gaps and separate/merge symbols
kernel2 = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
morphed = cv2.morphologyEx(cleaned, cv2.MORPH_CLOSE, kernel2)

# Show the stages
titles = ['Original', 'Background', 'Subtracted', 'Thresholded', 'Cleaned', 'Morphed']
images = [image, background, subtracted, thresh, cleaned, morphed]

for i in range(6):
    plt.subplot(2, 3, i + 1)
    plt.imshow(images[i], cmap='gray')
    plt.title(titles[i])
    plt.axis('off')

plt.tight_layout()
plt.savefig('output1.png')
print("Plot saved as output1.png")