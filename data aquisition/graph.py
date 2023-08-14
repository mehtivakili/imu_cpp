# Import matplotlib.pyplot and numpy modules
import matplotlib.pyplot as plt
import numpy as np

# Load the data from the file using np.genfromtxt
# The delimiter is ' ' (space) and the data is unpacked into four arrays
t, x, y, z = np.genfromtxt('revised_data1.txt', delimiter='\t', unpack=True)

# Plot the data using plt.plot function
# Use different colors and labels for each array
plt.plot(t, x, color='red', label='x')
plt.plot(t, y, color='green', label='y')
plt.plot(t, z, color='blue', label='z')

# Add title, xlabel, ylabel and legend to the plot
plt.title('IMU Accelerometer Data')
plt.xlabel('Time (s)')
plt.ylabel('Acceleration (counts)')
plt.legend()

# Show the plot
plt.show()
