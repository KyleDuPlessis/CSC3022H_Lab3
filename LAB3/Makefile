# DPLKYL002
# Makefile in ./DPLKYL002_LAB3 project folder to compile the driver and link it against the newly created shared libraries

CPP=g++ 
INCLUDES=-I./libs/findslib
LIBDIRS=-L./libs/findslib
LIBS= -lfinds
CPPFLAGS=-std=c++11 $(INCLUDES) $(LIBDIRS) $(LIBS)
TARGET=Driver

# first compile - IMPLICIT PATTERN RULE for creating binary object files
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

# then link - LINKING RULE for linking binary object files together to create an executable
$(TARGET): Driver.o 
	$(CPP) -o $(TARGET) Driver.o $(CPPFLAGS)
  
# other rules
# never submit binary object / executable files
clean:
	@rm *.o Driver
	@rm ./libs/*.so
	cd ./libs/findslib && make clean

# build entire project
all:
	cd ./libs/findslib && make
	@cp -f ./libs/findslib/*.so ./libs
	make

# run program
run finds:
	chmod 700 Driver
	export LD_LIBRARY_PATH=./libs && ./Driver $(args)


