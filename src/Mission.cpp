#include <string>
#include "Robot.hpp"
#include "Mission.hpp"

Mission::Mission(Robot * robot_ptr)
{
	mission_name = "Unnamed Mission";
	robot = robot_ptr;
}
