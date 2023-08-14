# Import csv
import csv

# Open the input file for reading
with open("acc_u.txt", "r") as input_file:
    # Create a csv reader object with tab as the delimiter
    reader = csv.reader(input_file, delimiter="\t")
    # Open the output file for writing
    with open("revised_data1.txt", "w") as output_file:
        # Create a csv writer object with tab as the delimiter
        writer = csv.writer(output_file, delimiter="\t")
        # Loop through each row in the input file
        for row in reader:
            # Try to scale the x, y, and z columns by (3600/2700)
            try:
                # Get the time column
                time = row[0]
                # Get the x, y, and z columns and scale them by (3600/2700)
                x = float(row[1]) * (3600/2700)
                y = float(row[2]) * (3600/2700)
                z = float(row[3]) * (3600/2700)
                # Format the scaled numbers as scientific notation with two digits after the decimal point and upper case E
                x = format(x, '.2E')
                y = format(y, '.2E')
                z = format(z, '.2E')
                # Write the formatted row to the output file
                writer.writerow([time, x, y, z])
            # If an IndexError occurs, print a message and skip the row
            except IndexError:
                print(f"Invalid row: {row}")
