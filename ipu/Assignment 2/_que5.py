import cv2
import matplotlib.pyplot as plt

# Load the two images
img1 = cv2.imread('image1.png', cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread('image2.png', cv2.IMREAD_GRAYSCALE)

# Check if images are loaded
if img1 is None or img2 is None:
    print("Error: One or both images not found!")
    exit()

# Create a SIFT detector
sift = cv2.SIFT_create()

# Detect keypoints and compute descriptors
kp1, des1 = sift.detectAndCompute(img1, None)
kp2, des2 = sift.detectAndCompute(img2, None)

# Use Brute-Force Matcher with default params
bf = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)

# Match descriptors
matches = bf.match(des1, des2)

# Sort matches by distance (best matches first)
matches = sorted(matches, key=lambda x: x.distance)

# Draw top 50 matches
matched_img = cv2.drawMatches(img1, kp1, img2, kp2, matches[:50], None, flags=2)

# Show the matched image using matplotlib
plt.figure(figsize=(12, 6))
plt.imshow(matched_img, cmap='gray')
plt.title('Top 50 Feature Matches using SIFT + Brute Force')
plt.axis('off')
plt.tight_layout()
plt.show()
