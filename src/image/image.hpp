/*
 * image.hpp
 *
 *  Created on: Aug 24, 2012
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_HPP_
#define NOKKHUM_IMAGE_HPP_

#include <chrono>
#include <ctime>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <opencv2/core/core.hpp>

namespace nokkhum {

enum MotionStatus {
	Undefine,
	BeginMotion,
	EndMotion,
};

class Image {
private:
	cv::Mat image;
	std::chrono::time_point<std::chrono::system_clock> date;

	MotionStatus motion_status = Undefine;
public:
	Image();
	Image(cv::Mat image);
	virtual ~Image();

	Image& operator >> (cv::Mat& image);
	Image& operator << (cv::Mat& image);

	cv::Mat get();
	cv::Mat clone();

	std::chrono::time_point<std::chrono::system_clock> getDate();

	void setMotionStatus(MotionStatus);
	MotionStatus getMotionStatus();


};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_HPP_ */
