from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

df_amylase = pd.read_csv("amylase_data.csv")

X = df_amylase[["Temperature", "pH", "Substrate_Amount"]]
y = df_amylase["Enzyme_Amount"]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

amylase_model = RandomForestRegressor(n_estimators=100, random_state=42)
amylase_model.fit(X_train, y_train)
