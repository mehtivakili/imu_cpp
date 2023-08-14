#include <iostream>
#include "imu_calib.h"


int main(int argc, char* argv[])
{
	std::vector<double> acce = {2.60000e+01,	6.40000e+01,	-2.74400e+03};
	std::vector<double> gyro = {8.00000e+00,	-6.00000e+00,	-1.50000e+01};

	std::vector<double> acce_calib(3, 0), gyro_calib(3, 0);

	// calibrate accelerameter
	// parameter for HUAWEI MATE 7
const std::vector<std::vector<double> > Ta = {{  1, -0.00546066, 0.00101399},
		 {0,          1, 0.00141895},
		 {0, 			0,          1}
};

const std::vector<std::vector<double> > Ka = {{0.00358347,     0,      0},
         {0, 0.00358133,          0},
         {0,      0,   0.00359205}

};

const std::vector<double> acce_bias = {-8.28051
,-4.6756
,-0.870355

};

     // calibrate gyroscope
 	// parameter for HUAWEI MATE 7
const std::vector<std::vector<double> > Tg = {{  1, -0.00614889, -0.000546488},
		{0.0102258,          1, 0.000838491},
		 {0.00412113, 0.0020154,          1}
};

const std::vector<std::vector<double> > Kg = {{0.000531972,    0,      0},
          {0, 0.000531541,           0},
          {0,           0,    0.000531}
};

const std::vector<double> gyro_bias = {4.53855
									,4.001
									,-1.9779
};
    Calibration calib;
    calib.set_acce_params(Ta, Ka, acce_bias);
    calib.set_gyro_params(Tg, Kg, gyro_bias);

	bool successed = calib.imu_calib(acce, gyro, acce_calib, gyro_calib);

	if(successed)
	{
		std::cout << "calibration successed!" << std::endl;
	}
	else
	{
		std::cout << "error, please check the input parameter!" << std::endl;
	}

	std::cout << acce_calib[0] << " " << acce_calib[1] << " " << acce_calib[2] << std::endl;
	std::cout << gyro_calib[0] << " " << gyro_calib[1] << " " << gyro_calib[2] << std::endl;
	
	return 0;
}