/* ===========================================================
Print data function   
Procedures::
1- Recieve type of data 
- Y::YAWPITCHROLL
- E::Euler-angels
2- Display data
==============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "Glib.h"

void Print_data(char Data_type)
{
	switch (Data_type)
	{
		case 'E':
		printf("euler %7.2f %7.2f %7.2f    ", euler[0] * 180/M_PI, euler[1] * 180/M_PI, euler[2] * 180/M_PI);
		printf("\n");
		break;

		case 'Y':
		printf("Yaw  %5.f    ", ypr[0] * 180/M_PI);
        printf("Pitch %5.f   " ,ypr[1] * 180/M_PI);
        printf("roll %5.f   " ,ypr[2] * 180/M_PI);
        printf("\n"); 
        break;
	}
}