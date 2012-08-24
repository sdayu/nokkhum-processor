/*
 * image.hpp
 *
 *  Created on: Aug 24, 2012
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_HPP_
#define NOKKHUM_IMAGE_HPP_

#include <chrono>
#include <opencv2/core/core.hpp>

namespace nokkhum {

class Image {
private:
	cv::Mat image;
	std::chrono::time_point<std::chrono::system_clock> date;
public:
	Image();
	Image(cv::Mat image);
	virtual ~Image();
	Image& operator >> (cv::Mat& image);
	Image& operator << (cv::Mat& image);

	cv::Mat get();

};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_HPP_ */
