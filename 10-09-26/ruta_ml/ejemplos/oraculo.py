import numpy as np, pandas as pd
from sklearn.linear_model import LogisticRegression

train = pd.read_csv("train.csv")
test = pd.read_csv("test.csv")

modelo = LogisticRegression(penalty=None, max_iter=1000)    # sin regularizar: el mismo problema que resolvio mi C++
modelo.fit(train[["x1", "x2"]], train["clase"])
w = modelo.coef_[0]
print(f"scikit-learn:     w = ({w[0]:.5g}, {w[1]:.5g})  b = {modelo.intercept_[0]:.5g}  "
      f"exactitud test = {modelo.score(test[['x1', 'x2']], test['clase']):.5g}")
