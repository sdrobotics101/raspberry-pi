#ifndef ContourDetector_hpp
#define ContourDetector_hpp

#include <vector>
#include <opencv2/opencv.hpp>
#include "Contour.hpp"

class ContourDetector {
 public:
	struct Params {
		Params();

		bool filter_by_hue;
		int min_hue;
		int max_hue;

		bool filter_by_saturation;
		int min_saturation;
		int max_saturation;

		bool filter_by_value;
		int min_value;
		int max_value;

		bool filter_by_area;
		int min_area;
		int max_area;

		bool filter_with_canny;
		int min_canny;
		int max_canny;

		bool filter_with_blur;
	};
	 ContourDetector(const ContourDetector::Params & parameters =
			 ContourDetector::Params());
	 std::vector < Contour > detect(cv::Mat image);
 private:
	 Params params;
};

#endif				// ContourDetector_hpp
