# import numpy for array operations
import numpy as np

# define a constant factor to multiply the raw data
factor = 0.00358867

# open the files for reading the raw data
with open("acc_u1.txt", "r") as acc_file, open("gyro_u1.txt", "r") as gyro_file:
    # open the files for writing the real data
    with open("acc_real.txt", "w") as acc_real_file, open("gyro_real.txt", "w") as gyro_real_file:
        # loop through the lines of the files
        for acc_line, gyro_line in zip(acc_file, gyro_file):
            # split the lines by tabs
            acc_line = acc_line.strip().split("\t")
            gyro_line = gyro_line.strip().split("\t")

            # get the time values from the first column
            acc_time = float(acc_line[0])
            gyro_time = float(gyro_line[0])

            # convert the strings to floats and skip the first column
            acc = [float(x) for x in acc_line[1:]]
            gyro = [float(x) for x in gyro_line[1:]]

            # convert the lists to numpy arrays
            acc = np.array(acc)
            gyro = np.array(gyro)

            # multiply the arrays by the factor
            acc_real = acc * factor
            gyro_real = gyro * factor

            # format the data as a string with tabs and include the time values
            acc_real_str = "{:.5e}\t{:.5e}\t{:.5e}\t{:.5e}\n".format(acc_time, acc_real[0], acc_real[1], acc_real[2])
            gyro_real_str = "{:.5e}\t{:.5e}\t{:.5e}\t{:.5e}\n".format(gyro_time, gyro_real[0], gyro_real[1], gyro_real[2])

            # write the data to the files
            acc_real_file.write(acc_real_str)
            gyro_real_file.write(gyro_real_str)
