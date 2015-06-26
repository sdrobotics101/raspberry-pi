#ifndef RPIVideoDevice_hpp
#define RPIVideoDevice_hpp

#include <thread>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "BaseVideoDevice.hpp"

class RPIVideoDevice:public BaseVideoDevice {
 public:
	RPIVideoDevice();
	virtual void start();
	 virtual ~ RPIVideoDevice();
 protected:
	 virtual void init_camera();
	virtual void capture_from_camera();
	 raspicam::RaspiCam_Cv camera;
};

#endif				// RPIVideoDevice_hpp
