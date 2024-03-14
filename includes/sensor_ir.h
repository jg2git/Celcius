/**********************************************************************************************************************
* Filename:sensor_ir.h;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the declarations for the IR temperature sensor.
*
************************************************************************************************************************/

#ifndef H_SENSOR_THERMAL
#define H_SENSOR_THERMAL
#include <sensor_thermal.h>
#endif
#include <string>

namespace q_coding {


class sensor_ir : public sensor_thermal {
	public:
	sensor_ir();                          //default constructor
	sensor_ir(std::string sensor_name);
	~sensor_ir();                         //default destructor
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
	std::string sensor_name;                      //Name of the sensor
	unsigned int baud_rate;                       //Communication interface baud rate
        unsigned int node_address;                    //Communication node address
        unsigned int reg_address;                     //Register address of the data to be read from
	int sensor_type;                              //Sensor device type
	
	//Member functions that interact with the low level code or C functions
	private:
	int connect(void);       //connect to the sensor
	int reset(void);         // reset the sensor
	int disconnect(void);    //terminate the connection
	int clean_up(void);      //disconnect if there is communication and cleanup up the resources
	
};

}
