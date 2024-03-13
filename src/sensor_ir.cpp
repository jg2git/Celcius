/**********************************************************************************************************************
* Filename:sensor_ir.cpp;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the definitions of the IR sensor. This class provides the services of the IR sensor to the 
* application. It serves as the interface between the application layer and the driver calls that interact with the 
* lower level hardware interaction software.
*
************************************************************************************************************************/

#include "sensor_ir.h"
#include <iostream>
#include <chrono>

namespace q_coding {	
/**********************************************************************************************************************
* Member name: Default constructor
* Arg: - 
* return: - 
* Description - Default constructor of the temperature sensor that initialises with a default name.
*
***********************************************************************************************************************/

sensor_ir::sensor_ir() : sensor_name("Qblox IR Temperature Sensor"), sensor_type(SENSOR_IR)
{

}
/**********************************************************************************************************************
* Member name: Parametrised constructor
* Arg: std::string sensor_name
* return -
* Description - Constructor of the temperature sensor that initialses with a sensor name as a parameter.
*
***********************************************************************************************************************/
sensor_ir::sensor_ir(std::string sensor_name) : sensor_name(sensor_name), sensor_type(SENSOR_IR)
{
    
}

/**********************************************************************************************************************
* Member name: Default destructor
* Arg: - 
* return: - 
* Description: - Default constructor of the temperature sensor.
*
***********************************************************************************************************************/
sensor_ir::~sensor_ir()
{
}

/**********************************************************************************************************************
* Member name: setup_sensor
* Arg: unsigned int inode_address, unsigned int ireg_address, unsigned int ibaud_rate
* return: int
* Description: Initialises the temperature sensor with respect to its specific protocol and allocates and initialises 
* the resources. We check for errors in parameters and setup the internal parameters necessary to communicate with the hardware.
* We connect with the device and also setup the state of the connection. 
*
* For simulating a temperature sensor's functionality, we initialise a random seed generator in this code. 
*
***********************************************************************************************************************/

int sensor_ir::setup_sensor(unsigned int inode_address, unsigned int ireg_address, unsigned int ibaud_rate)
{
	int status = 0;
	
	//Check for boundary errors
    if((inode_address > MAX_NODE_ADDR_RANGE) || (ireg_address > MAX_REG_ADDR_RANGE) || (ibaud_rate > MAX_BAUD_RATE) || (ibaud_rate < MIN_BAUD_RATE) )
		return -1;
	
	srand(time(NULL));                         //Random number generator to provide us a simulation of temperature values
	node_address = inode_address;              //Initialise the parameters from the input data    
	reg_address = ireg_address;
	baud_rate = ibaud_rate;
	
	//Call the low level C functions to initialise the drivers
	
	conn_state = SENSOR_INITIALIZED;          //Update the state machine to keep track of the state of the device
	status = connect();                       //Connect to the device
	if(!status)
		conn_state = SENSOR_CONNECTED_STATE;  //Update the state machine based on the state of the connection 
	else
		conn_state = SENSOR_ERROR;
	return status;
}

/**********************************************************************************************************************
* Member name: connect
* Arg: void
* return: int
* Description: Setups the lower level sensor comm stack for connecting with the sensor and starts the conection procedure. 
* Currently the implementation is a stub or unspecified.
*
***********************************************************************************************************************/
int sensor_ir::connect(void)
{
	//Call the lower level calls (in C) to connect with the device in its specific protocol
	return 0;
}

/**********************************************************************************************************************
* Member name: disconnect
* Arg: void
* return: int
* Description: Setups the parameters for the sensor comm stack for disconnecting with the sensor and executes the 
* disconnection procedure.
* Currently the implementation is a stub or unspecified.
*
***********************************************************************************************************************/
int sensor_ir::disconnect(void)
{
	//Call the lower level calls (in C) to disconnect gracefully with the device in its specific protocol
	return 0;
}
/**********************************************************************************************************************
* Member name: reset
* Arg: void
* return: int
* Description: Setups the parameters for the sensor comm stack for disconnecting and then restarting the connection.
* Currently the implementation is a stub or unspecified.
*
***********************************************************************************************************************/
int sensor_ir::reset(void)
{
	//Call the lower level calls (in C) to reset the connection
	return 0;
}
/**********************************************************************************************************************
* Member name: clean_up
* Arg: void
* return: int
* Description: Disconnect the communication with the sensor, deallocates the resources and updates the device state.
* Currently the implementation is a stub or unspecified.
*
***********************************************************************************************************************/
int sensor_ir::clean_up(void)      
{
	//Call the lower level calls (in C) to shutdown the connection and give up the resources
	return 0;
}

/**********************************************************************************************************************
* Member name - read_sensor
* Arg: void
* return: int
* Description: Read from the sensor queue from the lower level calls, extract the data for the calling function.
* 
* Currently the implementation is with a random generator and updates the sensor_data variable.
*
***********************************************************************************************************************/
int sensor_ir::read_sensor(float &read_data)      
{
	//Read from the sensor, extract and process the data 
	//In our case we will generate the sensor value with a simple random generator
	const int MULT_FACTOR = 10;
	float random_number = std::rand() % (SENSOR_MAX_TEMP*MULT_FACTOR);
	sensor_data = random_number/MULT_FACTOR;                      //Update the internal variable
	read_data = sensor_data;                                      //Pass back the temperature data to the calling routine
    
	return 0;
}

/**********************************************************************************************************************
* Member name: get_threshold
* Arg: bool& threshold
* return: int
* Description: Check the sensor data with the set point and update the alarm flag as true if the 
* read value in the database exceeds the threshold and vice versa.
*
***********************************************************************************************************************/
int sensor_ir::check_threshold(bool& alarm)    
{
	if(sensor_data > alarm_threshold)                            //Check if the temperature is above the threshold
		alarm = true;                                            //Update the alarm value as true
	else
		alarm = false;                                           //Update the alarm value as false
	
	return 0;
}
/**********************************************************************************************************************
* Member name: set_threshold
* Arg: float setpoint
* return: int
* Description: Check if the threshold setpoint is greater than the maximum allowed value and then update the setpoint.
* Return 0 if the threshold set point is updated, else send an error code.
***********************************************************************************************************************/
int sensor_ir::set_threshold(float setpoint)     
{
	if(setpoint <= SENSOR_MAX_TEMP)                            //Check for boundary error
	{
		alarm_threshold = setpoint;                            //Update the setpoint
		return 0;
	}
	else
		return -1;
}

/**********************************************************************************************************************
* Member name: get_threshold
* Arg: float& threshold
* return: int
* Description: Pass back the value of the set point in the internal database to the calling function.
***********************************************************************************************************************/
int sensor_ir::get_threshold(float& setpoint)     
{
	setpoint = alarm_threshold;                               //Pass back the setpoint value
	return 0;
}

/**********************************************************************************************************************
* Member name: print_param
* Arg: void
* return: int
* Description: Print the internal attributes of the sensor for debugging purposes.
***********************************************************************************************************************/
int sensor_ir::print_param(void)
{
	std::cout << "sensor_data " << sensor_data << std::endl ; //Print out the internal data values for debugging or display
	std::cout << "alarm_threshold " << alarm_threshold << std::endl;
	
 	return 0;
}
/**********************************************************************************************************************
* Member name: get_sensor_name
* Arg: std::string &isensor_name
* return: int
* Description: Pass back the sensor name to the calling function.
***********************************************************************************************************************/
int sensor_ir::get_sensor_name(std::string &isensor_name)
{
	isensor_name = sensor_name;                               //Pass back the sensor name
	return 0;
}

/**********************************************************************************************************************
* Member name: shutdown_sensor
* Arg: void
* return: int
* Description - Check if the device is connected or not. If connected, first disconnect and then clean up. If the device
* is not connected, cleanup the resources and reset the connection.
***********************************************************************************************************************/
int sensor_ir::shutdown_sensor(void)     
{
	if(conn_state == SENSOR_CONNECTED_STATE)                 //Check if the device is connected
	{
	    disconnect();                                        //Disconnect the device 
	    clean_up();                                          //Cleanup the resources
	}
	else
	{
		clean_up();                                          //Cleanup the resources 
	}
	conn_state = SENSOR_RESET_STATE;                         //Reset the state machine
	return 0;
}
/**********************************************************************************************************************
* Member name: get_internal_param
* Arg: float& isensor_data, float& ialarm_threshold, int& iconn_state, int& ierror
* return: int
* Description: Pass back the internal parameters to the calling function.
***********************************************************************************************************************/
int sensor_ir::get_internal_param(float& isensor_data, float& ialarm_threshold, int& iconn_state, int& ierror)
{
	isensor_data = sensor_data;                             //Pass back required the internal parameters to the calling function
	ialarm_threshold = alarm_threshold;
	iconn_state = conn_state;
	ierror = error;
	return 0;
}

}