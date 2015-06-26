#include <stdlib.h>
#include <iostream>
#include <thread>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include "BaseVideoDevice.hpp"
#include "RPIVideoDevice.hpp"

 RPIVideoDevice::RPIVideoDevice():BaseVideoDevice()
{
	focal_length = (3.6e-3) / (1.4e-6);
}

void RPIVideoDevice::start()
{
	init_camera();
	capture_thread =
	    new std::thread(&RPIVideoDevice::capture_from_camera, this);
}

void RPIVideoDevice::init_camera()
{
	camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	if (!camera.open()) {
		std::cerr << "Unable to open Raspberry Pi camera device." <<
		    std::endl;
		exit(EXIT_FAILURE);
	}
}

void RPIVideoDevice::capture_from_camera()
{
	cv::Mat unflipped;
	while (!is_finished) {
		camera.grab();
		camera.retrieve(unflipped);
		cv::flip(unflipped, image, -1);
		is_ready = true;
	}
}

RPIVideoDevice::~RPIVideoDevice()
{
	is_finished = true;
	capture_thread->join();
	delete capture_thread;
}
