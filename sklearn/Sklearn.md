# Sklearn

- sklearn.model_selection.train_test_split()

  ```python
  import numpy as np
  from sklearn.model_selection import train_test_split
  X, y = np.arange(10).reshape((5, 2)), range(5)
  X_train, X_test, y_train, y_test = train_test_split(
  ...     X, y, test_size=0.33, random_state=42)
  >>> X_train
  array([[4, 5],
         [0, 1],
         [6, 7]])
  >>> y_train
  [2, 0, 3]
  >>> X_test
  array([[2, 3],
         [8, 9]])
  >>> y_test
  [1, 4]
  ```

  

- sklearn.linear_model.LogisticRegression

  ```python
  class sklearn.linear_model.LogisticRegression(penalty=’l2’, dual=False, tol=0.0001, C=1.0, fit_intercept=True, intercept_scaling=1, class_weight=None, random_state=None, solver=’warn’, max_iter=100, multi_class=’warn’, verbose=0, warm_start=False, n_jobs=None)
  ```

- from sklearn.model_selection import StratifiedKFold

  Stratified K-Folds cross-validator

  Provides train/test indices to split data in train/test sets.

- OneHotEncoder

  - Encode categorical integer features as a one-hot numeric array.
  - fit(self,X[,y])   Fit OneHotEncoder to X.
  - fit_transform(self, X[, y])    Fit OneHotEncoder to X, then transform X.
  - transform(self, X)    Transform X using one-hot encoding.

- LabelEncoder

  - Encode labels with value between 0 and n_classes-1.
  - fit(self. y)  Fit label encoder
  - fit_transform(self, y)  Fit label encoder and return encoded labels
  - transform(self, y)   Transform labels to normalized encoding

  