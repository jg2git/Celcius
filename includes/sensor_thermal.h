/**********************************************************************************************************************
* Filename:sensor_thermostat.h;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the declarations for the temperature sensor abstract class.
*
************************************************************************************************************************/


#include <string>

namespace q_coding {

const int SENSOR_MAX_TEMP = 80;                   //Default max allowable temperature
const int MAX_NODE_ADDR_RANGE = 2000;             //Sensor device node address
const int MAX_REG_ADDR_RANGE = 0x2FF;             //Temperature register address
const int MIN_BAUD_RATE = 5000;                   //Device communication min baud rate
const int MAX_BAUD_RATE = 3000000;                //Device communication max baud rate

enum {
		SENSOR_RESET_STATE = 0,
		SENSOR_INITIALIZED,
		SENSOR_CONNECTED_STATE,
		SENSOR_DISCONNECTING_STATE,
		SENSOR_CLEANUP_STATE,
		SENSOR_ERROR
} CONN_STATE; //States of the sensor device

enum {
	SENSOR_THERMOSTAT = 0,
	SENSOR_IR
} DEVICE_TYPE;

class sensor_thermal {
	public:
	sensor_thermal();                          //default constructor
	sensor_thermal(std::string sensor_name);
	~sensor_thermal();                         //default destructor
	//Member functions of the class
	virtual int check_threshold(bool& alarm) = 0;             //Checks the threshold
	virtual int read_sensor(float &read_data) = 0;            //Reads from the sensor
	virtual int set_threshold(float setpoint) = 0;            //(Possible to use template for varying the data type)
	virtual int setup_sensor(unsigned int node_address, unsigned int reg_address, unsigned int baud_rate) = 0;   //initialize the sensor
	virtual int print_param(void) = 0;                        //Print the values of the attributes of the sensor	
	virtual int get_sensor_name(std::string& sensor_name) = 0;//Get sensor name
        virtual int shutdown_sensor(void) = 0;                    //Shutdowns the sensor
	virtual int get_threshold(float& setpoint) = 0;           //Gets the threshold that is already set
        virtual int get_internal_param(	float& sensor_data, float& sensor_alarm_threshold, int& conn_state, int& error) = 0;
	
	protected:
	//Member variables of the class that holds information about the sensor
    
	int sensor_type;
	float sensor_data;
	float alarm_threshold;
	int conn_state;
	int error;
	
	
};

}
