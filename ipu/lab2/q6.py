import cv2
import numpy as np

# Load video
cap = cv2.VideoCapture('traffic.mp4')

if not cap.isOpened():
    print("Error: Could not open video.")
    exit()

# Get video dimensions
ret, sample_frame = cap.read()
if not ret:
    print("Error: Cannot read frames.")
    cap.release()
    exit()

h, w = sample_frame.shape[:2]
print(f"[INFO] Frame resolution: {w}x{h}")

# Rewind and collect background frames
cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
frames = []
for i in range(30):
    ret, frame = cap.read()
    if not ret:
        break
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frames.append(gray)

median_background = np.median(frames, axis=0).astype(np.uint8)

# Confirm background ready
print("[INFO] Background model (median frame) is prepared.")

# Rewind video
cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

print("[INFO] Starting motion detection...")

frame_count = 0

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame_count += 1

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    diff = cv2.absdiff(gray, median_background)
    _, thresh = cv2.threshold(diff, 30, 255, cv2.THRESH_BINARY)

    # Morphological cleaning
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
    mask = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel)
    mask = cv2.dilate(mask, kernel, iterations=2)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    moving_objects = 0
    if contours:
        print(f"\n[Frame {frame_count}] Moving objects detected:")
        for cnt in contours:
            area = cv2.contourArea(cnt)
            if area > 500:
                moving_objects += 1
                x, y, w, h = cv2.boundingRect(cnt)
                print(f"  - Object {moving_objects}: Position (x={x}, y={y}), Size (w={w}, h={h}), Area: {area:.2f}")
    else:
        print(f"\n[Frame {frame_count}] No moving objects detected.")

cap.release()
print("\n[INFO] Motion detection completed.")
