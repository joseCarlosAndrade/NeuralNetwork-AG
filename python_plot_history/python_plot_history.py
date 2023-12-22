import pandas as pd
import matplotlib.pyplot as plt

# Replace 'your_file.csv' with the actual path to your CSV file
csv_file = '../build/Debug/evol_data/history.csv'

# Read the CSV file into a pandas DataFrame
df = pd.read_csv(csv_file, header=None)

# Extract the two lines from the DataFrame
best_fitness = df.iloc[0, :].values
mean_fitness = df.iloc[1, :].values

# Plot the evolution of best fitness and mean fitness
plt.plot(best_fitness, label='Best Fitness')
plt.plot(mean_fitness, label='Mean Fitness')
plt.xlabel('Generation')
plt.ylabel('Fitness')
plt.title('Evolution of Best and Mean Fitness')
plt.grid()
plt.legend()
plt.show()