#include <opencv2/opencv.hpp>
#include "Contour.hpp"
#include "ContourDetector.hpp"
#include "HSVImage.hpp"

ContourDetector::Params::Params()
{
	filter_by_hue = false;
	min_hue = 0;
	max_hue = 255;

	filter_by_saturation = false;
	min_saturation = 0;
	max_saturation = 255;

	filter_by_value = false;
	min_value = 0;
	max_value = 255;

	filter_by_area = false;
	min_area = 0;
	max_area = 1e6;

	filter_with_canny = true;
	min_canny = 0;
	max_canny = 50;

	filter_with_blur = true;
}

ContourDetector::ContourDetector(const ContourDetector::
				 Params & parameters):params(parameters)
{
}

std::vector < Contour > ContourDetector::detect(cv::Mat image)
{
	HSVImage hsv_image = HSVImage(image);
	cv::Mat hue_thresholded_lower;
	cv::Mat hue_thresholded_upper;
	cv::Mat hue_thresholded;
	cv::Mat saturation_thresholded_lower;
	cv::Mat saturation_thresholded_upper;
	cv::Mat saturation_thresholded;
	cv::Mat value_thresholded_lower;
	cv::Mat value_thresholded_upper;
	cv::Mat value_thresholded;
	cv::Mat threshold_out;
	cv::Mat blur_out;
	cv::Mat canny_out;
	cv::Mat processed_img;
	cv::threshold(hsv_image.hue, hue_thresholded_lower, params.min_hue, 255,
		      CV_THRESH_BINARY);
	cv::threshold(hsv_image.hue, hue_thresholded_upper, params.max_hue, 255,
		      CV_THRESH_BINARY_INV);
	hue_thresholded = hue_thresholded_lower & hue_thresholded_upper;
	cv::threshold(hsv_image.saturation, saturation_thresholded_lower,
		      params.min_saturation, 255, CV_THRESH_BINARY);
	cv::threshold(hsv_image.saturation, saturation_thresholded_upper,
		      params.max_saturation, 255, CV_THRESH_BINARY_INV);
	saturation_thresholded =
	    saturation_thresholded_lower & saturation_thresholded_upper;
	cv::threshold(hsv_image.value, value_thresholded_lower,
		      params.min_value, 255, CV_THRESH_BINARY);
	cv::threshold(hsv_image.value, value_thresholded_upper,
		      params.max_value, 255, CV_THRESH_BINARY_INV);
	value_thresholded = value_thresholded_lower & value_thresholded_upper;
	threshold_out = hue_thresholded.clone();
	if (params.filter_by_saturation)
		threshold_out = threshold_out & saturation_thresholded;
	if (params.filter_by_value)
		threshold_out = threshold_out & value_thresholded;
	if (params.filter_with_blur) {
		cv::Mat blur_tmp;
		cv::pyrDown(threshold_out, blur_tmp,
			    cv::Size(threshold_out.cols / 2,
				     threshold_out.rows / 2));
		cv::pyrUp(blur_tmp, blur_out, threshold_out.size());
	} else
		blur_out = threshold_out.clone();
	if (params.filter_with_canny) {
		cv::Canny(blur_out, canny_out, params.min_canny,
			  params.max_canny, 5);
		cv::dilate(canny_out, canny_out, cv::Mat(), cv::Point(-1, -1));
	} else
		canny_out = blur_out.clone();
	std::vector < std::vector < cv::Point > >all_contours_raw;
	cv::findContours(canny_out, all_contours_raw, CV_RETR_LIST,
			 CV_CHAIN_APPROX_SIMPLE);
	std::vector < Contour > all_contours;
	for (uint i = 0; i < all_contours_raw.size(); i++)
		all_contours.push_back(Contour(all_contours_raw.at(i)));
	std::vector < Contour > area_filtered_contours;
	if (params.filter_by_area) {
		for (uint i = 0; i < all_contours.size(); i++) {
			if (all_contours.at(i).get_area() > params.min_area
			    && area_filtered_contours.at(i).get_area() <
			    params.max_area)
				area_filtered_contours.push_back(all_contours.
								 at(i));
		}
	} else
		area_filtered_contours = all_contours;

	return area_filtered_contours;
}
