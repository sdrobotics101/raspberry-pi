#ifndef Mission_hpp
#define Mission_hpp

#include <string>
#include "Robot.hpp"

class Mission {
 public:
	virtual void run() = 0;
 protected:
	 Mission(Robot * robot_ptr);
	 std::string mission_name;
	Robot *robot;
};

#endif				// Mission_hpp
