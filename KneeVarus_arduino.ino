
#include <SparkFunMPU9250-DMP.h>
#include <SimpleKalmanFilter.h>
#define SerialPort SerialUSB

MPU9250_DMP imu;
SimpleKalmanFilter roll_k(1, 1, 0.05);
SimpleKalmanFilter pitch_k(1, 1, 0.075);
void setup() 
{
  SerialPort.begin(115200);

  if (imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("Unable to communicate with MPU-9250");
      SerialPort.println("Check connections, and try again.");
      SerialPort.println();
      delay(5000);
    }
  }

  imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);

  // Use setGyroFSR() and setAccelFSR() to configure the
  // gyroscope and accelerometer full scale ranges.
  // Gyro options are +/- 250, 500, 1000, or 2000 dps
  imu.setGyroFSR(2000); // Set gyro to 2000 dps
  // Accel options are +/- 2, 4, 8, or 16 g
  imu.setAccelFSR(16); // Set accel to +/-2g
  // Note: the MPU-9250's magnetometer FSR is set at 
  // +/- 4912 uT (micro-tesla's)
  imu.dmpBegin(DMP_FEATURE_GYRO_CAL |DMP_FEATURE_SEND_CAL_GYRO|DMP_FEATURE_SEND_RAW_ACCEL, 40);                   // Set DMP rate to 10 Hz
  // setLPF() can be used to set the digital low-pass filter
  // of the accelerometer and gyroscope.
  // Can be any of the following: 188, 98, 42, 20, 10, 5
  // (values are in Hz).
  imu.setLPF(10); // Set LPF corner frequency to 5Hz

  // The sample rate of the accel/gyro can be set using
  // setSampleRate. Acceptable values range from 4Hz to 1kHz
  imu.setSampleRate(40); // Set sample rate to 10Hz


}

void loop() 
{
    if ( imu.fifoAvailable() )
  {
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if ( imu.dmpUpdateFifo() == INV_SUCCESS)
    {
      printIMUData();
    }
  }

}

void printIMUData(void)
{  


  // Use the calcAccel, calcGyro, and calcMag functions to
  // convert the raw sensor readings (signed 16-bit values)
  // to their respective units.
  float accelX = imu.calcAccel(imu.ax);
  float accelY = imu.calcAccel(imu.ay);
  float accelZ = imu.calcAccel(imu.az);
  float gyroX = imu.calcGyro(imu.gx);
  float gyroY = imu.calcGyro(imu.gy);
  float gyroZ = imu.calcGyro(imu.gz);
  float p,  rollk,  pitchk ;
  float y ;
  float r ;
 // accelX = aX_k.updateEstimate(aX);
 // accelY = aY_k.updateEstimate(aY);
    r = atan(accelY / sqrt(pow(accelX, 2) + pow(accelZ, 2))) * 180 / PI;
    p = atan(-1 * accelX / sqrt(pow(accelY, 2) + pow(accelZ, 2))) * 180 / PI;
    rollk = roll_k.updateEstimate(r);
    pitchk = pitch_k.updateEstimate(p);

  SerialPort.println(pitchk);          // printing only one orientation which is same for 2nd imu too
 

}
