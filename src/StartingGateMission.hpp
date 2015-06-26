#ifndef StartingGateMission_hpp
#define StartingGateMission_hpp

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Robot.hpp"
#include "Contour.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Mission.hpp"

class StartingGateMission:public Mission {
 public:
	StartingGateMission(Robot * robot_ptr);
	virtual void run();
 protected:
	 void detect_gate();
	 std::vector < Circle > contours_to_circles(std::vector < Contour >
						    contours);
	 std::vector < Rectangle > contours_to_rectangles(std::vector <
							  Contour > contours);
	 std::vector < Rectangle > filter_rectangles(std::vector < Contour >
						     detected_contours);
	 std::vector < cv::Point2f > find_centroids(std::vector < Rectangle >
						    rectangles);
	double find_angular_displacement(std::vector < cv::Point2f > centroids,
					 cv::Point2f image_center);
	double find_depth_displacement(std::vector<cv::Point2f> centroids, cv::Point2f image_center);
	 std::string mission_name;
	Robot *robot;
	bool gate_detected;
	double angular_displacement;
	double depth_displacement;
};

#endif				// StartingGateMission_hpp
