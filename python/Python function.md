#Python function
- `np.concatenate`
Join a sequence of arrays along an existing axis.
- `np.asarray`
Convert the input to an array
- `sklearn.tree.DecisionTreeClassifier`
```python class sklearn.tree.DecisionTreeClassifier(criterion=’gini’, splitter=’best’, max_depth=None, min_samples_split=2, min_samples_leaf=1, min_weight_fraction_leaf=0.0, max_features=None, random_state=None, max_leaf_nodes=None, min_impurity_decrease=0.0, min_impurity_split=None, class_weight=None, presort=False)```

- `sklearn.metrics.pairwise.rbf_kernel`
Compute the rbf (gaussian) kernel between X and Y:
K(x, y) = exp(-gamma ||x-y||^2)
kernel_matrix : array of shape (n_samples_X, n_samples_Y)
- `cvxopt`
可以解线性规划和二次规划的问题
$$min \ 1/2x^TPx+q^Tx   $$
$$ s.t. Gx \leq h$$
$$ Ax=b$$
####example:
```python
from cvxopt import matrix, solvers
P = matrix([[1.0, 0.0], [0.0, 0.0]])
q = matrix([3.0, 4.0])
G = matrix([[-1.0, 0.0, -1.0, 2.0, 3.0], [0.0, -1.0, -3.0, 5.0, 4.0]])
h = matrix([0.0, 0.0, -15.0, 100.0, 80.0])

sol=solvers.qp(P, q, G, h)
print(sol['x'])
print(sol['primal objective'])
```
- `np.vstack`
Stack arrays in sequence vertically (row wise).
按行堆叠得到数组（每行）
```python
a=np.array([1,2,3])
b=np.array([2,3,4])
np.vstack((a,b))
array([[1,2,3],[2,3,4]])
```
- `np.median`
Compute the median along the specified axis,The default is to compute the median along a flattened version of the array
- `keepdims`
If this is set to True, the axes which are reduced are left in the result as dimensions with size one.
若原来为二维数组，求和后得到的仍为二维数组(n,1)，而不是一维数组(n,)
- `广播操作`
```python
a=np.array([1,2,3]).reshape(3,1)
b=np.array([6,7,0,4]).reshape(1,4)
a+b
array([[ 7,  8,  1,  5],
       [ 8,  9,  2,  6],
       [ 9, 10,  3,  7]])
```
- `sklearn.svm.svc`
```class sklearn.svm.SVC(C=1.0, kernel=’rbf’, degree=3, gamma=’auto_deprecated’, coef0=0.0, shrinking=True, probability=False, tol=0.001, cache_size=200, class_weight=None, verbose=False, max_iter=-1, decision_function_shape=’ovr’, random_state=None)```
The multiclass support is handled according to a one-vs-one scheme.

- `sample_weight`
Per-sample weights. Rescale C per sample. Higher weights force the classifier to put more emphasis on these points.

###matlab和Python间的.mat文件格式转换
```
import scipy.io as sio
import numpy as np
###下面是讲解python怎么读取.mat文件以及怎么处理得到的结果###
load_fn = 'xxx.mat'
load_data = sio.loadmat(load_fn)
load_matrix = load_data['matrix'] #假设文件中存有字符变量是matrix，例如matlab中save(load_fn, 'matrix');当然可以保存多个save(load_fn, 'matrix_x', 'matrix_y', ...);
load_matrix_row = load_matrix[0] #取了当时matlab中matrix的第一行，python中数组行排列
###下面是讲解python怎么保存.mat文件供matlab程序使用###
save_fn = 'xxx.mat'
save_array = np.array([1,2,3,4])
sio.savemat(save_fn, {'array': save_array}) #和上面的一样，存在了array变量的第一行
save_array_x = np.array([1,2,3,4])
save_array_y = np.array([5,6,7,8])
sio.savemat(save_fn, {'array_x': save_array_x, 'array_x': save_array_x}) #同理，只是存入了两个不同的变量供使用
```
- `np.isnan`
出现数值问题时判断哪一处出错
为什么一个矩阵求距离矩阵时出现数值问题？？？

### pycharm的debug
通过pycharm的debug可查看变量值




