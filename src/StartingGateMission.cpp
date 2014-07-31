/* StartingGateMission.cpp -- Implementation of StartingGateMission class

   Copyright (C) 2014 Tushar Pankaj
   
   This file is part of San Diego Robotics 101 Robosub.
   
   San Diego Robotics 101 Robosub is free software: you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.
   
   San Diego Robotics 101 Robosub is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with San Diego Robotics 101 Robosub.  If not, see
   <http://www.gnu.org/licenses/>. */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Robot.hpp"
#include "Logger.hpp"
#include "Contour.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "ContourDetector.hpp"
#include "DepthController.hpp"
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
	cv::Point2f mag_original = sample_magnetometer();
	DepthController depth_controller = DepthController(robot, 1.5, 0.1, 0.0);
	depth_controller.set_depth(60);
	robot->get_serial()->get_tx_packet()->set_vel_x(32);
	while (true)
	{
		cv::Point2f mag_current = sample_magnetometer();
		double angle = get_angle(mag_original, mag_current);
		robot->get_serial()->get_tx_packet()->set_rot_z((int8_t)(angle * 127.0 / 180.0));
	}
	/*while (!gate_detected)
		detect_gate();
	int no_detect_count = 0;
	while (no_detect_count < 30)
	{
		detect_gate();
		if (gate_detected)
		{
			robot->get_serial()->get_tx_packet()->set_rot_z((int8_t)(angular_displacement * 127.0 / 180.0));
			no_detect_count = 0;
		}
		else
			no_detect_count++;
	}
	while (true)
	{
	}*/
}

double StartingGateMission::get_angle(cv::Point2f v1, cv::Point2f v2)
{
	//return acos((v1.x*v2.x+v1.y*v2.y)/(sqrt(pow(v1.x,2)+pow(v1.y,2))*sqrt(pow(v2.x,2)+pow(v2.y,2)))) * 180.0 / M_PI;
	return asin((v2.y-v1.y)/(v2.x-v1.y)) * 180.0 / M_PI;
}

cv::Point2f StartingGateMission::sample_magnetometer()
{
	cv::Point2f sample_avg(0.0, 0.0);
	int sample_count = 16;
	for (int i = 0; i < sample_count; i++)
	{
		sample_avg += cv::Point2f(robot->get_serial()->get_rx_packet()->get_mag_y(), robot->get_serial()->get_rx_packet()->get_mag_x());
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	sample_avg.x /= (float)sample_count;
	sample_avg.y /= (float)sample_count;
	return sample_avg;
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
