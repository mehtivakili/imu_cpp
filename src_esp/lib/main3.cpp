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
double Tio = 0.000;
void setup() 
{
  int status;
  /* USB Serial to print data */
  Serial.begin(115200);
  while(!Serial) {}
  /* start the sensors */
  status = accel.begin();
  if (status < 0) {
    // Serial.println("Accel Initialization Error");
    // Serial.println(status);
    while (1) {}
  }
  status = gyro.begin();
  if (status < 0) {
    // Serial.println("Gyro Initialization Error");
    // Serial.println(status);
    while (1) {}
  }
    accel.setOdr(Bmi088Accel::ODR_1600HZ_BW_280HZ);
    gyro.setOdr(Bmi088Gyro::ODR_2000HZ_BW_532HZ);

}

void loop() 
{
  /* read the accel */
  accel.readSensor();
  /* read the gyro */
  gyro.readSensor();
  /* print the data */

          Serial.print(Tio);
          // Serial.print(",");
          Serial.print("\t");
          Serial.print((int) accel.getAccelX_mss());
          // Serial.print(",");
          Serial.print("\t");
          Serial.print((int) accel.getAccelY_mss());
          Serial.print("\t");
          Serial.print((int) accel.getAccelZ_mss());
          Serial.print("\t");
          Serial.print((int) gyro.getGyroX_rads());
          Serial.print("\t");
          Serial.print((int) gyro.getGyroY_rads());
          Serial.print("\t");
          Serial.print((int) gyro.getGyroZ_rads());
          // Serial.print(accel.getTemperature_C());
          Serial.print("\n");
  /* delay to help with printing */
  delay(10);
  Tio += 0.01;
}

// sudo chown mehdi:dialout /dev/ttyUSB0

