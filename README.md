# Celcius
## Qblox Temperature Alarm Project V0.1.0

This repository contains the source code for the Celcius C++ project that performs temperature data acquisition and triggers an alarm based on a threshold.

## Features
The project implements the following features 
- Interface to communicate with one or more temperature sensor devices
- Periodically poll a list of sensors
- Compare the current temperature with a threshold to trigger a threshold
- GTest unit test cases to test the functionalities

## Project files
\src
- sensor_thermistor.cpp - Communicates with the low level stack to interact with the temperature sensor to read the data
- data_acq.cpp - Initialises, polls and checks a list of temperature sensors for current temperature values which are used to compare with a threshold to trigger an alarm incase of overshoot.
- celcius.cpp - Main file that sets up and runs the application.

\test
- test_sensor_thermistor.cpp, test_data_acq.cpp and test_celcius.cpp are the unit test files that are used to test the application source files with Google Test framework.

## Building from source
Currently the build is supported for only the Linux bash environment. Run the makefile from the project base directory to recursively build the project and to update the build folder with the application and unit test binaries.

For compiling the project:

$:/Celcius/# make 

For cleaning the project:

$:/Celcius/# make clean

The binary output files in build/bin after a successful compilation are
- celcius - application binary file
- celcius_test - unit test binary file

## Requirements
- C++14 or later

## Tested platform
- Windows WSL Linux Work 4.4.0-19041-Microsoft #3996-Microsoft Thu Jan 18 16:36:00 PST 2024 x86_64 x86_64 x86_64 GNU/Linux 

## Coming up next
- Implementation of low level calls to the sensor
- Error handling mechanism
- Improved user interaction
