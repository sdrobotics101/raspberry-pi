#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Robot.hpp"
#include "Logger.hpp"
#include "Contour.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "ContourDetector.hpp"
#include "Mission.hpp"
#include "StartingGateMission.hpp"

 StartingGateMission::StartingGateMission(Robot * robot_ptr):Mission(robot_ptr)
{
	mission_name = "Starting Gate Mission";
	gate_detected = false;
}

void StartingGateMission::run()
{
	robot->get_logger()->write("Running mission " + mission_name, Logger::MESSAGE);
	robot->get_serial()->get_tx_packet()->set_vel_x(64);
	while (!gate_detected)
		detect_gate();
}

void StartingGateMission::detect_gate()
{
	cv::Mat image = robot->get_forward_camera()->get_image();
	ContourDetector::Params detector_params;
	detector_params.filter_by_hue = true;
	detector_params.min_hue = 100;
	detector_params.max_hue = 150;
	detector_params.max_canny = 50;
	detector_params.filter_with_blur = false;
	ContourDetector detector(detector_params);
	std::vector < Contour > contours = detector.detect(image);
	if (contours.empty()) {
		robot->get_logger()->write("No contours found",
					   Logger::WARNING);
		gate_detected = false;
		return;
	}
	std::vector < Rectangle > filtered_rectangles =
		filter_rectangles(contours);
	if (filtered_rectangles.empty()) {
		robot->get_logger()->
			write("No filtered rectangles found",
			      Logger::WARNING);
		gate_detected = false;
		return;
	}
	std::vector < cv::Point2f > centroids =
		find_centroids(filtered_rectangles);
	cv::Point2f image_center = cv::Point2f((float)image.rows / 2.0, (float)image.cols / 2.0);
	angular_displacement = find_angular_displacement(centroids, image_center);
	robot->get_logger()->write("StartingGateMission angular displacement is " + std::to_string(angular_displacement) + " degrees", Logger::VERBOSE);
	depth_displacement = find_depth_displacement(centroids, image_center);
	gate_detected = true;
}

std::vector < Circle > StartingGateMission::contours_to_circles(std::vector <
								Contour >
								contours)
{
	std::vector < Circle > circles;
	for (uint i = 0; i < contours.size(); i++)
		circles.push_back(Circle(contours.at(i).get_points()));
	return circles;
}

std::vector < Rectangle >
    StartingGateMission::contours_to_rectangles(std::vector < Contour >
						contours)
{
	std::vector < Rectangle > rectangles;
	for (uint i = 0; i < contours.size(); i++)
		rectangles.push_back(Rectangle(contours.at(i).get_points()));
	return rectangles;
}

std::vector < Rectangle > StartingGateMission::filter_rectangles(std::vector <
								 Contour >
								 detected_contours)
{
	std::vector < Circle > detected_enclosing_circles =
	    contours_to_circles(detected_contours);
	std::vector < Rectangle > detected_bounding_rectangles =
	    contours_to_rectangles(detected_contours);
	std::vector < Rectangle > filtered_rectangles;
	for (uint i = 0; i < detected_contours.size(); i++)	// Filter out circular contours and filter on aspect ratio
	{
		if (detected_bounding_rectangles.at(i).get_area_ratio() <
		    detected_enclosing_circles.at(i).get_area_ratio()
		    && detected_bounding_rectangles.at(i).get_aspect_ratio() <
		    0.2)
			filtered_rectangles.push_back
			    (detected_bounding_rectangles.at(i));
	}
	return filtered_rectangles;
}

std::vector < cv::Point2f > StartingGateMission::find_centroids(std::vector <
								Rectangle >
								rectangles)
{
	cv::Mat data = cv::Mat::zeros(rectangles.size(), 2, CV_32F);
	for (uint i = 0; i < rectangles.size(); i++) {
		data.at < float >(i, 0) = rectangles.at(i).get_center().x;
		data.at < float >(i, 1) = rectangles.at(i).get_center().y;
	}
	int K = 2;
	cv::Mat best_labels;
	cv::TermCriteria criteria =
	    cv::TermCriteria(cv::TermCriteria::COUNT, 10, 1.0);
	int attempts = 3;
	int flags = cv::KMEANS_PP_CENTERS;
	cv::Mat centroids;
	cv::kmeans(data, K, best_labels, criteria, attempts, flags, centroids);
	std::vector < cv::Point2f > centroids_vector;
	for (int i = 0; i < centroids.rows; i++)
		centroids_vector.push_back(cv::Point2f
					   (centroids.at < float >(i, 0),
					    centroids.at < float >(i, 1)));
	return centroids_vector;
}

double StartingGateMission::find_angular_displacement(std::vector <
						      cv::Point2f > centroids,
						      cv::Point2f image_center)
{
	cv::Point2f centroids_average = cv::Point2f(0.0, 0.0);
	for (uint i = 0; i < centroids.size(); i++)
		centroids_average += centroids.at(i);
	centroids_average.x /= centroids.size();
	centroids_average.y /= centroids.size();
	return robot->get_forward_camera()->pixels_to_angle((centroids_average -
							     image_center).x);
}

double StartingGateMission::find_depth_displacement(std::vector<cv::Point2f> centroids, cv::Point2f image_center)
{
	cv::Point2f centroids_average = cv::Point2f(0.0, 0.0);
	for (uint i = 0; i < centroids.size(); i++)
		centroids_average += centroids.at(i);
	centroids_average.x /= centroids.size();
	centroids_average.y /= centroids.size();
	return (centroids_average - image_center).y;
}
