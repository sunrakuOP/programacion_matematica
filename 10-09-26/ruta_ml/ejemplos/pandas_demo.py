import pandas as pd

df = pd.read_csv("train.csv")
print(df.shape, "filas x columnas")
print(df.groupby("clase")[["x1", "x2"]].agg(["mean", "std"]).round(3))
