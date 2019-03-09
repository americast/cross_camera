import h5py
import numpy as np
import cv2
import pudb

arrays = {}
print("Reading mat file started")
f = h5py.File("detections/DPM/camera1.mat")
for k, v in f.items():
	arrays[k] = np.array(v)
print("Reading mat file completed")

cap = cv2.VideoCapture("videos/camera1/00000.MTS")

frame_no = 1
glob_count = 0
arr_no = 0
features = []

def extract_colour_histogram(image, bins=(8, 8, 8)):
	hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
	hist = cv2.calcHist([hsv], [0, 1, 2], None, bins, [0, 180, 0, 256, 0, 256]) 
	cv2.normalize(hist, hist)
	return hist.flatten()

while cap.isOpened():
    ret, frame = cap.read()
    if not ret: break
    count = 1
    min_dist = 999999999
    loc = 0
    print("\n\nDistances:")
    while True:
    	arr = arrays["detections"][...,arr_no]
    	if arr[1] != frame_no:
    		break
    	arr_no+=1
    	if arr[-1] > 0:
    		cut_out = frame[int(arr[3]):int(arr[5]), int(arr[2]):int(arr[4])]
    		if glob_count == 0:
    			# cv2.imshow("cropped", cut_out)
    			# if cv2.waitKey(0) == ord('q'):
    			# 	pass
    			features = extract_colour_histogram(cut_out)
    			glob_count += 1
    			# pu.db
    		frame = cv2.rectangle(frame, (int(arr[2]), int(arr[3])),(int(arr[4]), int(arr[5])), (0,0,0), 2)
    		features_here = extract_colour_histogram(cut_out)
    		dist_here = np.sum(np.fabs(features_here - features))
    		print(dist_here)
    		if (dist_here < min_dist):
    			min_dist = dist_here
    			loc = (int(arr[2]), int(arr[3]))
    		cv2.putText(frame, str(count), (int(arr[2]), int(arr[3])), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (255, 0, 0))

    	count+=1
    try:
    	if min_dist < 5:
    		cv2.putText(frame, "  This", loc, cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255, 0))
    except:
    	pass
    cv2.imshow("out", frame)
    cv2.waitKey(1)
    frame_no+=1

pu.db
     

