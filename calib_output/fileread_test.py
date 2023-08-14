# import numpy for matrix operations
import numpy as np

# define a class for calibration
class Calibration:
    def __init__(self):
        # initialize the parameters for accelerometer and gyroscope
        self.Ta = None # transformation matrix for accelerometer
        self.Ka = None # scaling matrix for accelerometer
        self.acce_bias = None # bias vector for accelerometer
        self.Tg = None # transformation matrix for gyroscope
        self.Kg = None # scaling matrix for gyroscope
        self.gyro_bias = None # bias vector for gyroscope
    
    def set_acce_params(self, Ta, Ka, acce_bias):
        # set the parameters for accelerometer
        self.Ta = np.array(Ta) # convert to numpy array
        self.Ka = np.array(Ka) # convert to numpy array
        self.acce_bias = np.array(acce_bias) # convert to numpy array
    
    def set_gyro_params(self, Tg, Kg, gyro_bias):
        # set the parameters for gyroscope
        self.Tg = np.array(Tg) # convert to numpy array
        self.Kg = np.array(Kg) # convert to numpy array
        self.gyro_bias = np.array(gyro_bias) # convert to numpy array
    
    def imu_calib(self, acce, gyro):
        # calibrate the accelerometer and gyroscope data
        try:
            # convert the input vectors to numpy arrays
            acce = np.array(acce)
            gyro = np.array(gyro)

            # check the dimensions of the input vectors
            if acce.shape != (3,) or gyro.shape != (3,):
                raise ValueError("The input vectors must have dimension 3")

            # check if the parameters are set
            if self.Ta is None or self.Ka is None or self.acce_bias is None or self.Tg is None or self.Kg is None or self.gyro_bias is None:
                raise ValueError("The parameters must be set before calibration")

            # calibrate the accelerometer data
            acce_calib = self.Ta @ (self.Ka @ (acce - self.acce_bias))

            # calibrate the gyroscope data
            gyro_calib = self.Tg @ (self.Kg @ (gyro - self.gyro_bias))

            # return True and the calibrated data if calibration is successful
            return True, acce_calib, gyro_calib
        
        except Exception as e:
            # print the error message and return False and None if calibration fails
            print(e)
            return False, None, None

# create an instance of Calibration class
calib = Calibration()

# calibrate accelerameter
# parameter for HUAWEI MATE 7
Ta = [[  1, -0.00546066, 0.00101399],
      [0,          1, 0.00141895],
      [0, 			0,          1]
]

Ka = [[0.00358347,     0,      0],
      [0, 0.00358133,          0],
      [0,      0,   0.00359205]
]

acce_bias = [-8.28051,
             -4.6756,
             -0.870355]

# calibrate gyroscope
# parameter for HUAWEI MATE 7
Tg = [[  1, -0.00614889, -0.000546488],
      [0.0102258,          1, 0.000838491],
      [0.00412113, 0.0020154,          1]
]

Kg = [[0.000531972,    0,      0],
      [0, 0.000531541,           0],
      [0,           0,    0.000531]
]

gyro_bias = [4.53855,
             4.001,
             -1.9779]

# set the parameters for calibration
calib.set_acce_params(Ta, Ka, acce_bias)
calib.set_gyro_params(Tg, Kg, gyro_bias)

# create empty lists to store the calibrated data
acce_calib_list = []
gyro_calib_list = []

# open the files for reading the data
with open("acc_u1.txt", "r") as acc_file, open("gyro_u1.txt", "r") as gyro_file:
    # loop through the lines of the files
    for acc_line, gyro_line in zip(acc_file, gyro_file):
        # split the lines by tabs
        acc_line = acc_line.strip().split("\t")
        gyro_line = gyro_line.strip().split("\t")

        # convert the strings to floats and skip the first column
        time = [float(x) for x in acc_line[0]]
        acce = [float(x) for x in acc_line[1:]]
        gyro = [float(x) for x in gyro_line[1:]]

        # calibrate the data
        successed, acce_calib, gyro_calib = calib.imu_calib(acce, gyro)

        # check if calibration is successful
        if successed:
            print("calibration successed!")
        else:
            print("error, please check the input parameter!")
            break

        # append the calibrated data to the lists
        acce_calib_list.append(acce_calib)
        gyro_calib_list.append(gyro_calib)

# open the files for writing the calibrated data
with open("acc_calibrated.txt", "w") as acc_calib_file, open("gyro_calibrated.txt", "w") as gyro_calib_file:
    # loop through the calibrated data
    for acce_calib, gyro_calib in zip(acce_calib_list, gyro_calib_list):
        # format the data as a string with tabs
        acce_calib_str = time+"\t".join([str(x) for x in acce_calib]) + "\n"
        gyro_calib_str = time+"\t".join([str(x) for x in gyro_calib]) + "\n"

        # write the data to the files
        acc_calib_file.write(acce_calib_str)
        gyro_calib_file.write(gyro_calib_str)
