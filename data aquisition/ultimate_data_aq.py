import serial 
import struct
ser = serial.Serial ('/dev/ttyUSB0', 115200, timeout=1)
data_list = [] # create an empty list to store the data
write_start = True # create a boolean variable to indicate when the writing and printing should start
first_value = None # create a variable to store the first number[0] value
T0 = 50 # set the initial time interval for turning the imu
T1 = 6 # set the subsequent time intervals for turning the imu
Total_turn = 15
T = T0 + T1*Total_turn
turn_count = 0 # create a variable to count the number of turns
data = ser.read(28) # read 28 bytes from the serial port
numbers = struct.unpack('<7f',data) # unpack the data into a list of 7 floats

print(numbers)
while True: # start a loop
    data = ser.read(28) # read 28 bytes from the serial port
    numbers = struct.unpack('<7f',data) # unpack the data into a list of 7 floats
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
# print(data_list) # print the final data list

# create and open two text files named acc and gyro in write mode
acc_file = open("acc_u.txt", "w")
gyro_file = open("gyro_u.txt", "w")

# loop through the data list and write to the files
for numbers in data_list:
    # format each number as a string with scientific notation and 5 decimal places
    numbers = [format(n, ".5e") for n in numbers]
    # write the first parameter in the same line as the second to fourth parameters in the acc file, separated by tabs
    acc_file.write(numbers[0] + "\t" + "\t".join(numbers[1:4]) + "\n")
    # write the first parameter in the same line as the fifth to seventh parameters in the gyro file, separated by tabs
    gyro_file.write(numbers[0] + "\t" + "\t".join(numbers[4:7]) + "\n")

# close the files
acc_file.close()
gyro_file.close()
