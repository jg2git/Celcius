# Makefile for the source .cpp files
CXX = g++ # G++
INC_DIR = ../includes
GT_LIB = ../lib/gtest/
SRC_LIB = ../build/lib/
BLD_LDIR = ../build/lib/
BLD_BDIR = ../build/bin/
objects = test_sensor_thermostat.o test_data_acq.o test_celcius.o
CFLAGS = -c
CPFLAGS = -f
CLFLAGS = -f

all : $(objects) celcius copy remove
.PHONY : all

$(objects): %.o: %.cpp
	$(CXX) -I $(INC_DIR) -c $< -o $@

celcius:
	$(CXX) -I $(INC_DIR) test_sensor_thermostat.cpp test_data_acq.cpp -fPIC -shared -o celcius_test.so
	$(CXX) -I $(INC_DIR) $(objects) -pthread -destdir/lib $(GT_LIB)libgtest.a $(GT_LIB)libgtest_main.a $(SRC_LIB)sensor_thermostat.a $(SRC_LIB)sensor_thermal.a $(SRC_LIB)data_acq.a $(SRC_LIB)sensor_ir.a -o celcius_test

copy:
	cp $(CPFLAGS) celcius_test $(BLD_BDIR).
	cp $(CPFLAGS) celcius_test.so $(BLD_LDIR).

remove:
	rm -f *.so

clean:
	rm $(CLFLAGS) celcius_test *.a *.o *.so
	