/**********************************************************************************************************************
* Filename:sensor_thermostat.cpp;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the definitions of the thermal sensor base class. This class is used as the abstract class
* for the temperature sensors.
*
************************************************************************************************************************/

#include "sensor_thermal.h"
#include <iostream>
#include <chrono>
#include <string.h>

namespace q_coding {	
/**********************************************************************************************************************
* Member name: Default constructor
* Arg: - 
* return: - 
* Description - Default constructor of the temperature sensor that initialises with a default name.
*
***********************************************************************************************************************/

sensor_thermal::sensor_thermal()
{
	sensor_data = 0;
	alarm_threshold = 0;
	conn_state = 0;
	error = 0;
}


/**********************************************************************************************************************
* Member name: Default destructor
* Arg: - 
* return: - 
* Description: - Default constructor of the temperature sensor.
*
***********************************************************************************************************************/
sensor_thermal::~sensor_thermal()
{
}

}
