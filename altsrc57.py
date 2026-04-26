import numpy as np
a=np.array([[2,3,1],[1,1,2],[3,4,1]])
b=np.array([13,7,22])
x1=np.linalg.solve(a,b)
print("solution",x1)
a1=np.dot(a,x1)
print("check",a1)
