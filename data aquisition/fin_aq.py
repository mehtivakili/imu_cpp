import serial 
import struct

ser = serial.Serial ('COM5', 115200, timeout=1)

data_list = [] # create an empty list to store the data
write_start = True # create a boolean variable to indicate when the writing and printing should start
first_value = None # create a variable to store the first number[0] value
T0 = 5 # set the initial time interval for turning the imu
T1 = 6 # set the subsequent time intervals for turning the imu
Total_turn = 1
T = T0 + T1*Total_turn
turn_count = 0 # create a variable to count the number of turns

# modify the code to read 40 bytes instead of 28 bytes from the serial port
data = ser.read(40) # read 40 bytes from the serial port

# modify the code to unpack the data into a list of 10 floats instead of 7 floats
numbers = struct.unpack('<10f',data) # unpack the data into a list of 10 floats

print(numbers)
while True: # start a loop
    data = ser.read(40) # read 40 bytes from the serial port
    numbers = struct.unpack('<10f',data) # unpack the data into a list of 10 floats
    if numbers[0] == 0: # check if the first number is zero
        write_start = True # set the write_start variable to True
    if write_start: # check if the writing and printing should start
        if first_value is None: # check if the first_value variable is None
            first_value = numbers[0] # assign the first number[0] value to it
        numbers = list(numbers) # convert the tuple to a list
        numbers[0] -= first_value # subtract the first_value from the current number[0] value
        numbers = tuple(numbers) # convert the list back to a tuple
        # print(numbers) # print the numbers
        data_list.append(numbers) # append the numbers to the data list
        
        # check if it is time to turn the imu based on T0 and T1 values
        if numbers[0] >= T0 + turn_count * T1:
            turn_count += 1 # increment the turn count by one
            print("Turn the imu") # print a message to turn the imu
            print(f"n'th Turn:{turn_count}") # print a message to turn the imu
    if numbers[0] > T: # check if the first number is greater than 20
        break # exit the loop

# create and open one text file named imu in write mode
imu_file = open("imu_u.txt", "w")

# loop through the data list and write to the file
for numbers in data_list:
    # format each number as a string with scientific notation and 5 decimal places
    numbers = [format(n, ".5e") for n in numbers]
    # write all ten parameters in one line in the imu file, separated by tabs
    imu_file.write("\t".join(numbers) + "\n")

# close the file
imu_file.close()
