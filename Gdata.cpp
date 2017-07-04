/* ===========================================================
Get data function of the Gesture  
Procedures::
1- Check flag which it should be true if the setup finished with no error
2- Check memory state 
      --reset it if needed 
      --otherwise, check for DMP data ready interrupt 
3- Read the DMP data
4- Present data in three different form depend on user choice 
==============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "Glib.h"

/* uncomment "OUTPUT_READABLE_EULER" if you want to see Euler angles
  (in degrees) calculated from the quaternions coming from the FIFO.
  Note that Euler angles suffer from gimbal lock (for more info, see
  http://en.wikipedia.org/wiki/Gimbal_lock)*/
//#define OUTPUT_READABLE_EULER

/* uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
  pitch/roll angles (in degrees) calculated from the quaternions coming
  from the FIFO. Note this also requires gravity vector calculations.
  Also note that yaw/pitch/roll angles suffer from gimbal lock (for
  more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)*/
//#define OUTPUT_READABLE_YAWPITCHROLL
//Get data in four different forms 

void Getdata(char Data_type) 
{
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    if (fifoCount == 1024) 
    {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        printf("FIFO overflow!\n");

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } 
    else if (fifoCount >= 42) 
    {
        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);

        switch (Data_type)
        {
          case 'E':
           // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetEuler(euler, &q);
            break;
          case 'Y':
          // display YAWPITCHROLL
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        }
        
  }
}
