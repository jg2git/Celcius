/**********************************************************************************************************************
* Filename:test_data_acq.cpp;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the functions that does the unit testing of the data_acq class and its functionalities
* using GTest suite.
*
************************************************************************************************************************/

#include <data_acq.h>
#include "gtest/gtest.h"
#include <vector> 

using namespace std;
namespace q_coding {
/**********************************************************************************************************************
* Class: data_acq_test 
* 
* Description - Test class for GTest for the data acquisition application.
*
***********************************************************************************************************************/
class data_acq_test : public testing::Test {
 protected:

  data_acq_test() {
  }

  ~data_acq_test() override {
  }

  void SetUp() override {
  }

  void TearDown() override {
  }
};
/**********************************************************************************************************************
* Test function: test_init_devices
*
* Description - Test the initialisation of the devices by data_acq.
*
***********************************************************************************************************************/
TEST_F(data_acq_test, test_init_devices) 
{
	data_acq test_data_acq;
	EXPECT_EQ(test_data_acq.init_poll(), 0) << "Init poll failure.";         //Test if the initialisation has executed without error
}
/**********************************************************************************************************************
* Test function: test_poll_devices
*
* Description - Test the polling of the devices by data_acq.
*
***********************************************************************************************************************/
TEST_F(data_acq_test, test_poll_devices) 
{
	data_acq test_data_acq;
	const int TEST_ITERATIONS = 20;
	EXPECT_EQ(test_data_acq.init_poll(), 0) << "Init poll failure.";        //Test if the initialisation has executed without error
	for(auto i =0;i<TEST_ITERATIONS;i++)                                    //Iterate n times for the tests to proceed
	    EXPECT_EQ(test_data_acq.poll_devices(), 0) << "Init poll failure."; //Test for the polling functionality of the data acquisition application 
}
}
