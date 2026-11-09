import pandas as pd
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import cross_val_score

df = pd.read_csv("train.csv")
X, y = df[["x1", "x2"]], df["clase"]

# El StandardScaler vive DENTRO del pipeline: en cada pliegue se ajusta solo con los datos de entrenamiento (sin fuga)
for k in [1, 5, 15, 51]:
    modelo = make_pipeline(StandardScaler(), KNeighborsClassifier(n_neighbors=k))
    puntajes = cross_val_score(modelo, X, y, cv=5)
    print(f"k = {k:2d}:  exactitud 5-fold = {puntajes.mean():.3f} +/- {puntajes.std():.3f}")
