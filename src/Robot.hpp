#ifndef Robot_hpp
#define Robot_hpp

#include <string>
#include "Serial.hpp"
#include "Logger.hpp"
#include "BaseVideoDevice.hpp"

class Robot {
 public:
	Robot();
	~Robot();
	void set_period(int new_period);
	void autonomous_mode();
	void teleop_mode();
	BaseVideoDevice *get_forward_camera();
	BaseVideoDevice *get_downward_camera();
	Logger *get_logger();
	Serial *get_serial();
	void hreset_arduino();
 private:
	void autonomous_init();
	void teleop_init();
	void autonomous_periodic();
	void teleop_periodic();
	Serial serial;
	int period;
	 std::string int_base;
	double bat_v_threshold;
	int hreset_pin;
	BaseVideoDevice *forward_camera;
	BaseVideoDevice *downward_camera;
	Logger logger;
};

#endif				// Robot_hpp
