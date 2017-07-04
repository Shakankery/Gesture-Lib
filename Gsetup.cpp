/* ===========================================================
intializing function of the Gesture with default address 0x68 
Procedures::
1- Intialize the device
2- Test the connection 
3- Enable the DMP 
	which fuses the accelerometer and gyroscope data together 
	to minimize the effects of errors inherent in each sensor
4- Check for error and enable flag to start getting data 
==============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "Glib.h"

// intializing function with default address 0x68  

void Gsetup() 
{
    // initialize device
    printf("Initializing I2C devices...\n");
    mpu.initialize();

    // verify connection
    printf("Testing device connections...\n");
    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");

    // load and configure the DMP
    printf("Initializing DMP...\n");
    devStatus = mpu.dmpInitialize();
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) 
    {
        // turn on the DMP, now that it's ready
        printf("Enabling DMP...\n");
        mpu.setDMPEnabled(true);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        printf("DMP ready!\n");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } 
    else 
    {
        /* ERROR!
         1 = initial memory load failed
         2 = DMP configuration updates failed
        (if it's going to break, usually the code will be 1)*/
        printf("DMP Initialization failed (code %d)\n", devStatus);
    }
}
