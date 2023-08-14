/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2018 Bolder Flight Systems
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, 
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or 
* substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "BMI088.h"

/* accel object */
Bmi088Accel accel(SPI,32);
/* gyro object */
Bmi088Gyro gyro(SPI,25);

    int16_t accelX_raw, accelY_raw, accelZ_raw;
    int16_t gyroX_raw, gyroY_raw, gyroZ_raw;
// Bmi088 bmi(SPI,32,25);

double Tio = 0.000;
double myArray[7];
typedef union {
  float floatingPoint;
  byte binary[4];
} binaryFloat;

void setup() 
{
  int status;
  /* USB Serial to print data */
  Serial.begin(115200);
  while(!Serial) {}
  /* start the sensors */
  status = accel.begin(Bmi088Accel::RANGE_12G, Bmi088Accel::ODR_1600HZ_BW_234HZ);
  if (status < 0) {
    // Serial.println("Accel Initialization Error");
    // Serial.println(status);
    while (1) {}
  }
  status = gyro.begin(Bmi088Gyro::RANGE_1000DPS, Bmi088Gyro::ODR_2000HZ_BW_230HZ);
  if (status < 0) {
    // Serial.println("Gyro Initialization Error");
    // Serial.println(status);
    while (1) {}
  }
    // accel.setOdr(Bmi088Accel::ODR_1600HZ_BW_280HZ);
    // gyro.setOdr(Bmi088Gyro::ODR_2000HZ_BW_532HZ);
    accel.getSensorRawValues(&accelX_raw, &accelY_raw, &accelZ_raw );
    gyro.getSensorRawValues(&gyroX_raw, &gyroY_raw, &gyroZ_raw);

}

void loop() 
{
  /* read the accel */
  accel.readSensor();
  /* read the gyro */
  gyro.readSensor();
  /* print the data */
    accel.getSensorRawValues(&accelX_raw, &accelY_raw, &accelZ_raw);
    gyro.getSensorRawValues(&gyroX_raw, &gyroY_raw, &gyroZ_raw);
  //  printf("Raw Accelerometer (X,Y,Z): %d, %d, %d\n", accelX_raw, accelY_raw, accelZ_raw);
  //  printf("Raw Gyroscope (X,Y,Z): %d, %d, %d\n", gyroX_raw, gyroY_raw, gyroZ_raw);

  // myArray[0] = accel.getAccelX_mss();
  // myArray[1] = accel.getAccelY_mss();
  // myArray[2] = accel.getAccelZ_mss();
  // myArray[3] = gyro.getGyroX_rads();
  // myArray[4] = gyro.getGyroY_rads();
  // myArray[5] = gyro.getGyroZ_rads();
  // myArray[6] = Tio;
   
  myArray[0] = Tio;
  myArray[1] = accelX_raw;
  myArray[2] = accelY_raw;
  myArray[3] = accelZ_raw;
  myArray[4] = gyroX_raw;
  myArray[5] = gyroY_raw;
  myArray[6] = gyroZ_raw;
 
          // Serial.print(myArray[0]);
          // Serial.print("\t");
          // Serial.print(myArray[1]);
          // Serial.print("\t");
          // Serial.print(myArray[2]);
          // Serial.print("\t");
          // Serial.print(myArray[3]);
          // Serial.print("\t");
          // Serial.print(myArray[4]);
          // Serial.print("\t");
          // Serial.print(myArray[5]);
          // Serial.print("\t");
          // Serial.print(myArray[6]);
          // Serial.print("\n");


  size_t size = sizeof(myArray);

  for(int i = 0; i < 7 ; i++){
    binaryFloat hi;
    hi.floatingPoint = myArray[i];
    Serial.write(hi.binary,4);
  }
  
  // binaryFloat hi;
  // hi.floatingPoint = -11.7;
  // Serial.write(hi.binary,4);
          // Serial.print(Tio);
          // Serial.print("\t");
          // // Serial.print("\t");
          // Serial.print((int) accel.getAccelX_mss());
          // Serial.print("\t");
          // Serial.print((int) accel.getAccelY_mss());
          // Serial.print("\t");
          // Serial.print((int) accel.getAccelZ_mss());
          // Serial.print("\t");
          // Serial.print(gyro.getGyroX_rads());
          // Serial.print("\t");
          // Serial.print(gyro.getGyroY_rads());
          // Serial.print("\t");
          // Serial.print(gyro.getGyroZ_rads());
          // Serial.print("\t");
          // Serial.print(accel.getTemperature_C());
          // Serial.print("\n");
  /* delay to help with printing */
  delay(5);
  Tio += 0.005;
}

// sudo chown mehdi:dialout /dev/ttyUSB0
