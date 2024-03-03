/**********************************************************************************************************************
* Filename: data_acq.h;     
* Author: Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description: The file contains the declarations for the data acquisition functionality.
*
************************************************************************************************************************/

#ifndef H_SENSOR_THERMOSTAT
#define H_SENSOR_THERMOSTAT
#include "sensor_thermostat.h"
#endif

#include <string>
#include <vector>

namespace q_coding {
	
//Configuration data for temperature sensor A
const std::string SENSOR_A_NAME = "Qblox Temperature Sensor A";
const unsigned int SENSOR_A_NODE_ADDR = 0x01;
const unsigned int SENSOR_A_REG_ADDR = 0xAB;
const unsigned int SENSOR_A_BAUD = 115200;
const float SENSOR_A_THRESHOLD = 45.5;
//Configuration data for temperature sensor B	
const std::string SENSOR_B_NAME = "Qblox Temperature Sensor B";	
const unsigned int SENSOR_B_NODE_ADDR = 0x01;
const unsigned int SENSOR_B_REG_ADDR = 0xAB;	
const unsigned int SENSOR_B_BAUD = 115200;
const float SENSOR_B_THRESHOLD = 20;

const int SENSOR_A_TABLE_ENTRY = 0;
const int SENSOR_B_TABLE_ENTRY = 1;

class data_acq {
    public:
	data_acq();                                      //Default constructor
	~data_acq();                                     //Default destructor
	//Member functions of the class
	int init_poll(void);
	int poll_devices(void);
	int shutdown_devices(void);
	
	private:
	std::vector <sensor_thermostat*> sensor_poll;	//List of temperature sensor devices to be read from
};

}




