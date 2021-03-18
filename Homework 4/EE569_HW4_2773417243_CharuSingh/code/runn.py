import numpy as np
import matplotlib.pyplot as plt
plt.close('all')

def scale(X, x_min, x_max):
    nom = (X-X.min(axis=0))*(x_max-x_min)
    denom = X.max(axis=0) - X.min(axis=0)
    denom[denom==0] = 1
    return x_min + nom/denom 

X = np.loadtxt('result_train.txt')
# X = X[:,1]
X = X.reshape([36,15])
X = X.astype(int)

X_scaled = scale(X, 0, 100)
print(X_scaled)

label_colors = ['r','g','b','r','b','r','c','c','g','c','b','g']


for i in range(0,15):
    plt.figure()
    plt.bar(X_scaled[:,i], [1]*36, color=label_colors)
    plt.title('Feature '+str(i+1))
    plt.xlabel('Feature Values')
    plt.ylabel('Count')
    plt.savefig('feature_'+str(i+1)+'.png')