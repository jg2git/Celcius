# Makefile for the source .cpp files
CXX = g++ # G++
INC_DIR = ../includes
BLD_LDIR = ../build/lib/
BLD_BDIR = ../build/bin/
objects = sensor_thermostat.o data_acq.o celcius.o
CFLAGS = -c
CPFLAGS = -f
CLFLAGS = -f

all : $(objects) celcius static_lib copy remove
.PHONY : all

$(objects): %.o: %.cpp
	$(CXX) -I $(INC_DIR) -c $< -o $@


celcius:
	$(CXX) -I $(INC_DIR) $(objects) -o celcius
	$(CXX) -I $(INC_DIR) sensor_thermostat.cpp data_acq.cpp -fPIC -shared -o celcius.so

static_lib:
	ar rvs sensor_thermostat.a sensor_thermostat.o
	ar rvs data_acq.a data_acq.o

copy:
	cp $(CPFLAGS) *.a $(BLD_LDIR).
	cp $(CPFLAGS) *.so $(BLD_LDIR).
	cp $(CPFLAGS) celcius $(BLD_BDIR).

remove:
	rm -f *a *.so

clean:
	rm $(CLFLAGS) celcius *.a *.o *.so