import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from ipywidgets import widgets, VBox, Button, Output
from IPython.display import display

data = {
    "Enzyme": ["Amylase", "Lipase", "Protease", "Cellulase", "Lactase", "Catalase", "Urease", "Invertase", "Maltase", "Pectinase"],
    "Optimum_Temperature": [37, 40, 50, 45, 37, 30, 60, 35, 37, 45],
    "Optimum_pH": [7, 8, 7, 6, 6.5, 7, 7.5, 4.5, 6, 5]
}

df = pd.DataFrame(data)

X = df[["Optimum_Temperature", "Optimum_pH"]]
y_temp = df["Optimum_Temperature"]
y_pH = df["Optimum_pH"]

model_temp = LinearRegression().fit(X, y_temp)
model_pH = LinearRegression().fit(X, y_pH)

def predict_optimal_conditions(selected_enzymes):
    if not selected_enzymes:
        print("Please select at least one enzyme.")
        return
    selected_data = df[df["Enzyme"].isin(selected_enzymes)]
    avg_temp = selected_data["Optimum_Temperature"].mean()
    avg_pH = selected_data["Optimum_pH"].mean()
    print(f"Predicted Optimal Temperature: {avg_temp:.2f}°C")
    print(f"Predicted Optimal pH: {avg_pH:.2f}")

def interactive_interface():
    enzyme_checkboxes = [widgets.Checkbox(value=False, description=enzyme) for enzyme in df["Enzyme"]]
    button = Button(description="Predict")
    output = Output()

    def on_button_click(b):
        with output:
            output.clear_output()
            selected_enzymes = [checkbox.description for checkbox in enzyme_checkboxes if checkbox.value]
            predict_optimal_conditions(selected_enzymes)

    button.on_click(on_button_click)
    display(VBox(enzyme_checkboxes), button, output)

interactive_interface()