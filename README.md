# Knee-Varus-Thrust
This project aims to build a prototype that monitors the gait movement of the elderly people legs, who are likely to have knee varus thrust instead of going to a sophisticated gait laboratory. 
  Varus thrust is the visualized dynamic bowing out of the knee laterally while the limb is weightbearing (stance) during ambulation, with the return to a less varus alignment during nonweightbearing (swing). 
  Varus thrust can be assessed in a gait lab, where it is defined as the difference in the hip-knee-ankle angle between heel strike and the first varus peak.

The movement of the leg about the frontal or coronal plane of the human anatomy can be tracked using Sen14001- The SparkFun 9DoF Razor IMU which combines a SAMD21 microprocessor with an MPU-9250 9DoF (9 Degrees of Freedom) sensor was used in this project, 
which has a 3 Accelerometer, a 3 axis Gyroscope and a 3 axis Magnetometer. By using these sensors values Euler angles were calculated.

The two SparkFun sensors were mounted on the shank and thigh of the patient's leg. The raw data from IMU sensors is processed by ATSAM21 microcontroller and after applying filters,the Euler angles are calculated and real-time processing of the knee movement in the frontal plane using Pyserial, the data was shown on a live monitor to check whether he is likely to have Knee Varus Thrust or not.

* Arduino_KneeVarus.ino -> contains the final code of getting the values from sparkfun and filtering it and sends the values to python
* IMU_HIP.stl;IMU_knee.stl;IMU_plate.stl -> the complete CAD file for 3d printing the mount for placing the lipo and sparkfun board.
* KneeVarusThrust.docx -> contains reference links
* Python_KneeVarus.py  -> contains the final python code of getting the IMU values from 2 sparkfun boards and plot the knee angle in matplot.lib
* Report knee varus thrust.docx -> intern report
