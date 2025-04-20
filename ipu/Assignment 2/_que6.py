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
for i in range(600):
    ret, frame = cap.read()
    if not ret:
        break
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frames.append(gray)

median_background = np.median(frames, axis=0).astype(np.uint8)

# Show the median background for confirmation
cv2.imshow("Median Background", median_background)
print("[INFO] Showing median background — press any key to continue...")
cv2.waitKey(0)
cv2.destroyAllWindows()

# Rewind video
cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

print("[INFO] Starting motion detection...")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    diff = cv2.absdiff(gray, median_background)
    _, thresh = cv2.threshold(diff, 30, 255, cv2.THRESH_BINARY)

    # Morphological cleaning
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
    mask = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel)
    mask = cv2.dilate(mask, kernel, iterations=2)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if contours:
        for cnt in contours:
            area = cv2.contourArea(cnt)
            if area > 500:
                x, y, w, h = cv2.boundingRect(cnt)
                cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
    else:
        cv2.putText(frame, "No moving objects detected", (50, 50),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

    # Show output windows
    cv2.imshow('Vehicle Detection', frame)
    cv2.imshow('Foreground Mask', mask)

    key = cv2.waitKey(30)
    if key == 27:  # ESC key to break
        break

cap.release()
cv2.destroyAllWindows()