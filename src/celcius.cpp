/**********************************************************************************************************************
* Filename:celcius.cpp;     
* Author:Jonathan Gnanadhas
* The code was developed for a coding test from Qblox.
* License - Free to use
*
* Description:The file contains the main function that implements the functionality of initializing a list of sensors 
* for data acquisition and polls them in an interval.
*
************************************************************************************************************************/

#include "data_acq.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>


using namespace q_coding;
using namespace std;
using namespace std::chrono_literals;
const int WAIT_INTERVAL = 500;

/**********************************************************************************************************************
* Member name: main
* Arg: int argc, char* argv[]
* return: int
* Description: The main function of the program. It initialises the data acquisition application and executes the application,
* which polls the devices in a certain interval of time. 
*
***********************************************************************************************************************/

int main(int argc, char* argv[]) 
{
	data_acq qdata_acq;
	cout << "Initialising the devices..." << endl;
	qdata_acq.init_poll();                     //Initialise the application 
	cout << "Initialisation complete." << endl;
	cout << "Starting the application..." << endl;
	for(auto i=0;i<5;i++)
	{
		qdata_acq.poll_devices();             // Poll the devices and perform the functionalities 
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_INTERVAL));   // Pause for a given interval of time
	}
	cout << "Shutting down the devices..." << endl;
	qdata_acq.shutdown_devices();            //Shutdown the devices  
	cout << "Shutting down complete." << endl;
	return 0;
}
