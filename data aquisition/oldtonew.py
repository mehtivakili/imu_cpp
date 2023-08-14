# Open the text file in read mode
with open("acc_u.txt", "r") as f:
    # Read the lines of the file
    lines = f.readlines()
    # Create a new list to store the revised data
    revised_data = []
    # Loop through each line
    for line in lines:
        # Split the line by whitespace
        values = line.split()
        # Convert the values to floats
        values = [float(v) for v in values]
        # Subtract 32768 from the x, y, and z values
        values[1] -= 32768
        values[2] -= 32768
        values[3] -= 32768
        # Append the revised values to the new list
        revised_data.append(values)

# Open a new text file in write mode
with open("acc_o1.txt", "w") as f:
    # Loop through the revised data
    for values in revised_data:
        # Join the values by whitespace
        line = " ".join([str(v) for v in values])
        # Write the line to the file with a newline character
        f.write(line + "\n")
