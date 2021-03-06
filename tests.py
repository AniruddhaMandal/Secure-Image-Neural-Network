import numpy as np
import matplotlib.pyplot as plt 

# product test
A = np.genfromtxt("DEBUG/A.csv",delimiter=",")
B = np.genfromtxt("DEBUG/B.csv",delimiter=",")

product = np.genfromtxt("DEBUG/product.csv",delimiter=",")
np_product = A@B
print("product test",np.allclose(product,np_product))

#sum test
C = np.genfromtxt("DEBUG/C.csv",delimiter=",")
_sum = np.genfromtxt("DEBUG/sum.csv",delimiter=",")
new_sum = product + C

print("sum test: ",np.allclose(_sum,new_sum))

D = np.genfromtxt("DEBUG/D.csv",delimiter=",")
sig = np.genfromtxt("DEBUG/sig.csv",delimiter=",")

np_sig = 1/(1+np.exp(-D))
print("sigmoid test: ",np.allclose(sig,np_sig))

# random number generator test
randomArray = np.genfromtxt("build/testRandomNumber.csv",delimiter=",")
y,x = np.histogram(randomArray,100);
plt.bar(x[1:], y,width=0.01)
plt.show()