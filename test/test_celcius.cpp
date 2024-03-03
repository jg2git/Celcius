/**********************************************************************************************************************
* Filename:test_celcius.cpp;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the main function that initialises the GTest suite and runs the tests that are initialised
* with the framework.
*
************************************************************************************************************************/
#include <data_acq.h>
#include "gtest/gtest.h"
#include <vector> 

using namespace std;

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  cout << "Running unit tests..." << endl;
  return RUN_ALL_TESTS();
}
