/**********************************************************************************************************************
* Filename:test_sesnor_thermostat.cpp;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the functions that does the unit testing of the sensor functionalites using GTest suite.
*
************************************************************************************************************************/
#include <data_acq.h>
#include "gtest/gtest.h"
#include <vector> 

using namespace std;
namespace q_coding {
/**********************************************************************************************************************
* Class: sensor_test 
* 
* Description - Test class for GTest for the temperature sensor.
*
***********************************************************************************************************************/
class sensor_test : protected sensor_thermostat, public testing::Test {
 protected:

  sensor_test() {
  }

  ~sensor_test() override {
  }

  void SetUp() override {
  }

  void TearDown() override {
  }
};

/**********************************************************************************************************************
* Test function: test_setup_sensor
*
* Description - Test the initialisation or setup of the temperature sensor.
*
***********************************************************************************************************************/
TEST_F(sensor_test, test_setup_sensor) 
{
    sensor_thermostat test_sensor_t;
	float sensor_data = 0;
	float alarm_threshold = 0;
	int conn_state = 0;
	int error = 0;
	//Test the sensor device setup functionality
    EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE, MAX_BAUD_RATE), 0) << "Boundary test failure.";
	//Retrieve and check the internal parameters such as connection state 
	EXPECT_EQ(test_sensor_t.get_internal_param(sensor_data, alarm_threshold, conn_state, error), 0) << "Error retrieveing internal parameters.";
	EXPECT_EQ(conn_state, SENSOR_CONNECTED_STATE) << "State change variable error.";
	//Test for error conditions
    EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE+1, MAX_REG_ADDR_RANGE, MAX_BAUD_RATE), -1) << "Boundary test failure.";
    EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE+1, MAX_BAUD_RATE), -1) << "Boundary test failure.";
    EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE, MAX_BAUD_RATE+1), -1) << "Boundary test failure.";
    EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE, MIN_BAUD_RATE-1), -1) << "Boundary test failure.";
    EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE, MIN_BAUD_RATE), 0) << "Boundary test failure.";
    EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE, MAX_BAUD_RATE), 0) << "Boundary test failure.";
}
/**********************************************************************************************************************
* Test function: test_alarm
*
* Description - Test module for a regression test of the threshold functionality of the temperature sensor.
*
***********************************************************************************************************************/
TEST_F(sensor_test, test_alarm)
{
    const int TEST_ITERATIONS = 2000000;
	sensor_thermostat test_sensor_t;
	float sensor_data = 0;
	float alarm_threshold = 0;
	int conn_state = 0;
	int error = 0;
	//Test the sensor device setup functionality
	EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE, MAX_BAUD_RATE), 0) << "Boundary test failure.";
	//Retrieve and check the internal parameters such as connection state 
	EXPECT_EQ(test_sensor_t.get_internal_param(sensor_data, alarm_threshold, conn_state, error), 0) << "Error retrieveing internal parameters.";
	EXPECT_EQ(conn_state, SENSOR_CONNECTED_STATE) << "State change variable error.";
	//Start the regression test
	for(auto i=0;i<TEST_ITERATIONS;i++)
	{
		float read_data;
		bool alarm;
		float setpoint;
		
		EXPECT_EQ(test_sensor_t.read_sensor(read_data), 0) << "Read Sensor test failure.";     //Read the temperature from the sensor
		EXPECT_EQ(test_sensor_t.check_threshold(alarm), 0) << "Check threshold call failure."; //Check for the threshold
		EXPECT_EQ(test_sensor_t.get_threshold(setpoint), 0) << "Get threshold call failure.";  //Get the internal threshold
	    
		if(read_data > setpoint)                          //Check the functionality of the alarm flag
			EXPECT_TRUE(alarm) << "Alarm failure.";
		else
			EXPECT_FALSE(alarm) << "Alarm failure.";
		
	}
}
/**********************************************************************************************************************
* Test function: test_shutdown
*
* Description - Test module for testing the shutdown functionality of the temperature sensor.
*
***********************************************************************************************************************/
TEST_F(sensor_test, test_shutdown) 
{
	sensor_thermostat test_sensor_t;
	float sensor_data = 0;
	float alarm_threshold = 0;
	int conn_state = 0;
	int error = 0;
	//Test the sensor device setup functionality
	EXPECT_EQ(test_sensor_t.setup_sensor(MAX_NODE_ADDR_RANGE, MAX_REG_ADDR_RANGE, MAX_BAUD_RATE), 0) << "Boundary test failure.";
	//Retrieve and check the internal parameters such as connection state 
	EXPECT_EQ(test_sensor_t.get_internal_param(sensor_data, alarm_threshold, conn_state, error), 0) << "Error retrieveing internal parameters.";
	EXPECT_EQ(conn_state, SENSOR_CONNECTED_STATE) << "State change variable error.";
	//Test the sensor shutdown
	EXPECT_EQ(test_sensor_t.shutdown_sensor(), 0) << "Shutdown sensor test failure.";
	//Retrieve and check the internal parameters such as connection state 
	EXPECT_EQ(test_sensor_t.get_internal_param(sensor_data, alarm_threshold, conn_state, error), 0) << "Error retrieveing internal parameters.";
	EXPECT_EQ(conn_state, SENSOR_RESET_STATE) << "State change variable error.";
}
}

