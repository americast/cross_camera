import h5py
import numpy as np
import pudb

loc = "detections/DPM/"
file = "camera1.mat"

arrays = {}
print("Reading mat file started")
f = h5py.File(loc+file)
for k, v in f.items():
	arrays[k] = np.array(v)
print("Reading mat file completed")

f = open(loc+file+"_plaintext", "w")
print("Writing to file")

i = 0
while(True):
	print(str(i)+" / "+str(arrays["detections"].shape[1]))
	try:
		here = arrays["detections"][..., i]
	except:
		break
	for each in here:
		# pu.db
		f.write(str(float(each))+"\n")
	i+=1


f.close()


pu.db