import pandas as pd
from sklearn.linear_model import LinearRegression
import joblib

file_path = "./data.csv"

data = pd.read_csv(file_path)

y = data["Price"]
feature_columns = ["Month", "Supply"]
X = data[feature_columns]

model = LinearRegression()

model.fit(X, y)

def predict_months(months, supply):
    return model.predict(pd.DataFrame({"Month": months, "Supply":supply}))

# works with multiple inputs
print("Predictions:", predict_months([16,18,20,22], [10,11,15,18]))

# works with single input
print("Prediction for Month=30:", predict_months([30], [22]))

print("Intercept:", model.intercept_)
print("Coefficients:", dict(zip(feature_columns, model.coef_)))

joblib.dump(model, "price_model.pkl")