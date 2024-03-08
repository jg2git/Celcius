/**********************************************************************************************************************
* Filename:sensor_thermostat.h;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the declarations for the temperature sensor.
*
************************************************************************************************************************/


#include <string>

namespace q_coding {

const int SENSOR_MAX_TEMP = 80;                   //Default max allowable temperature
const int MAX_NODE_ADDR_RANGE = 2000;             //Sensor device node address
const int MAX_REG_ADDR_RANGE = 0x2FF;             //Temperature register address
const int MIN_BAUD_RATE = 5000;                   //Device communication min baud rate
const int MAX_BAUD_RATE = 3000000;                //Device communication max baud rate

class sensor_thermostat {
	public:
	sensor_thermostat();                          //default constructor
	sensor_thermostat(std::string sensor_name);
	sensor_thermostat(std::string sensor_name, unsigned int baud_rate, unsigned int node_address, unsigned int reg_address);
	~sensor_thermostat();                         //default destructor
	//Member functions of the class
	int check_threshold(bool& alarm);             //Checks the threshold
	int read_sensor(float &read_data);            //Reads from the sensor
	int set_threshold(float setpoint);            //(Possible to use template for varying the data type)
	int setup_sensor(unsigned int node_address, unsigned int reg_address, unsigned int baud_rate);   //initialize the sensor
	int print_param(void);                        //Print the values of the attributes of the sensor	
	int get_sensor_name(std::string& sensor_name);//Get sensor name
        int shutdown_sensor(void);                    //Shutdowns the sensor
	int get_threshold(float& setpoint);           //Gets the threshold that is already set
        int get_internal_param(	float& sensor_data, float& sensor_alarm_threshold, int& conn_state, int& error);
	
	protected:
		enum {
		SENSOR_RESET_STATE = 0,
		SENSOR_INITIALIZED,
		SENSOR_CONNECTED_STATE,
		SENSOR_DISCONNECTING_STATE,
		SENSOR_CLEANUP_STATE,
		SENSOR_ERROR
	} CONN_STATE;                                //States of the sensor device
	
	//Member variables of the class
        std::string sensor_name;
	unsigned int baud_rate;
        unsigned int node_address;
        unsigned int reg_address;
	float sensor_data;
	float alarm_threshold;
	int conn_state;
	int error;
	
	private:
	//Members that interact with the low level code or C functions
	int connect(void);       //connect to the sensor
	int reset(void);         // reset the sensor
	int disconnect(void);    //terminate the connection
	int clean_up(void);      //disconnect if there is communication and cleanup up the resources
	
};

}
