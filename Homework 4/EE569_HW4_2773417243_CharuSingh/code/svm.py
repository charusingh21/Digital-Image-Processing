from sklearn import svm



import struct
import matplotlib.pyplot as plt
import numpy as np
import random
import sys
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans

image_data = []
with open("result_train.txt") as f:
	for line in f:
		line = line.strip().split(" ")
		line = [float(x) for x in line]
		image_data.append(line)

image_data = np.array(image_data)

pca = PCA(n_components=2)
pca.fit(image_data)
image_data_3D = pca.transform(image_data)

# kmeans_15D = KMeans(n_clusters=4, random_state=0).fit(image_data)
# kmeans_3D = KMeans(n_clusters=4, random_state=0).fit(image_data_3D)

# cluster_labels_15D = kmeans_15D.predict(image_data)
# cluster_labels_3D = kmeans_3D.predict(image_data_3D)

first = [0]*9
sec = [1]*9
third = [2]*9
forth = [3]*9
first.extend(sec)
first.extend(third)
first.extend(forth)

print(len(image_data_3D), len(first), first)

svmClass_15D = svm.SVC(kernel='poly')
svmClass_15D.fit(image_data, first)


svmClass_3D = svm.SVC(kernel='poly')
svmClass_3D.fit(image_data_3D, first)


image_data = []
with open("result_test.txt") as f:
	for line in f:
		line = line.strip().split(" ")
		line = [float(x) for x in line]
		image_data.append(line)

image_data = np.array(image_data)

pca = PCA(n_components=2)
pca.fit(image_data)
image_data_3D = pca.transform(image_data)

cluster_labels_15D = svmClass_15D.predict(image_data)
cluster_labels_3D = svmClass_3D.predict(image_data_3D)

with open("svm_15D_train.txt", "w") as f:
	for label in cluster_labels_15D:
		f.write(str(label) + "\n")

with open("svm_3D_train.txt", "w") as f:
	for label in cluster_labels_3D:
		f.write(str(label) + "\n")
