#ifndef Robot_hpp
#define Robot_hpp

#include "Serial.hpp"

class Robot {
 public:
	int start();
 private:
	 Serial serial;
};

#endif				// Robot_hpp
