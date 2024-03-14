/**********************************************************************************************************************
* Filename:data_acq.cpp   
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the definitions of the data acquision object. This class is part of the
* the application layer that interacts with a list of sensors and extracts the temperature from it.
*
************************************************************************************************************************/

#include "data_acq.h"
#include <iostream>
#include <vector>
#include <string>

namespace q_coding {	
/**********************************************************************************************************************
* Member name: Default constructor
* Arg: - 
* return: - 
* Description: Default constructor of the data acquision class.
*
***********************************************************************************************************************/

data_acq::data_acq()
{
	
}
/**********************************************************************************************************************
* Member name: Default destructor
* Arg: - 
* return: - 
* Description: Default destructor of the data acquision class.
*
***********************************************************************************************************************/
data_acq::~data_acq()
{
	for(auto q_sensor:sensor_poll)
	{
		delete q_sensor;
	}
}
/**********************************************************************************************************************
* Member name: init_poll
* Arg: void
* return: int
* Description: Initialises a list of temperature devices that needs to be polled with the device parameters.
*
***********************************************************************************************************************/
int data_acq::init_poll(void)
{
	
	//It would be nicer to initialise this section from reading from a configuration file or a configuration data structure
	//We hardcode two temperature sensors
	
	if(sensor_poll.empty())
	     sensor_poll = { new sensor_thermostat(SENSOR_A_NAME),  new sensor_ir(SENSOR_B_NAME)};       //Allocate the list of sensors
	 else
		 return -1;
	
	sensor_poll[SENSOR_A_TABLE_ENTRY]->setup_sensor(SENSOR_A_NODE_ADDR, SENSOR_A_REG_ADDR, SENSOR_A_BAUD); //Initialise the sensors
	sensor_poll[SENSOR_A_TABLE_ENTRY]->set_threshold(SENSOR_A_THRESHOLD);                                  //Set the threshold
	sensor_poll[SENSOR_B_TABLE_ENTRY]->setup_sensor(SENSOR_B_NODE_ADDR, SENSOR_B_REG_ADDR, SENSOR_B_BAUD);
	sensor_poll[SENSOR_B_TABLE_ENTRY]->set_threshold(SENSOR_B_THRESHOLD);
	std::cout << SENSOR_A_NAME << " alarm is set at "<< SENSOR_A_THRESHOLD << std::endl;
	std::cout << SENSOR_B_NAME << " alarm is set at "<< SENSOR_B_THRESHOLD << std::endl;
	return 0;
}
/**********************************************************************************************************************
* Member name: poll_devices
* Arg: void
* return: int
* Description: Sequentially polls or reads the temperature from a list of sensors and checks if the temperature has exceeded a 
* threshold. If the temperature exceeds a threshold, then an alarm is triggered. 
*
***********************************************************************************************************************/
int data_acq::poll_devices(void)
{
	for(auto q_sensor:sensor_poll)                            //Get the sensor object from the sensor list or vector
	{
		float read_temp=0;
		bool alarm=false;
		std::string sensor_name;
		
	        q_sensor->read_sensor(read_temp);                     //Read the temperature from the sensor
		q_sensor->check_threshold(alarm);                     //Check the temperature with respect to the threshold and update the alarm if needed 
		q_sensor->get_sensor_name(sensor_name);               //Get the name of the sensor
		std::cout << sensor_name << ", Temperature: "<< read_temp << ", alarm state: " << alarm << std::endl; //Print the parameters for display
	}
	return 0;
}
/**********************************************************************************************************************
* Member name: shutdown_devices
* Arg: void
* return: int
* Description: Shuts down the sensor devices in the poll list. The shutdown triggers a termination of the connection 
* to the sensors and deallocates the resources.
*
***********************************************************************************************************************/
int data_acq::shutdown_devices(void)
{
	for(auto q_sensor:sensor_poll)                           //Get the sensor object from the sensor list or vector 
	{
	    q_sensor->shutdown_sensor();                         //Shut down the sensor
	}
	return 0;
}

}
