/*
 * image-recorder.cpp
 *
 *  Created on: Jun 27, 2011
 *      Author: boatkrap
 */

#include "image_recorder.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace nokkhum {

ImageRecorder::ImageRecorder(CvMatQueue &input_image_queue) :
		ImageProcessor("Image Recorder", input_image_queue) {
	// TODO Auto-generated constructor stub

}

ImageRecorder::~ImageRecorder() {
	// TODO Auto-generated destructor stub
}

void ImageRecorder::start() {
	cv::Mat frame;
	while (running) {

		while (input_image_queue.empty()) {
			usleep(100);
		}

		frame = input_image_queue.pop();

		time_t rawtime;
		time ( &rawtime );
		tm* time_struct =  localtime(&rawtime);

		std::string record_name;
		std::ostringstream oss;
		oss << time_struct->tm_year+1900
				<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_mon+1
				<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_mday
				<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_hour
				<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_min
				<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_sec
				<< ".png";

		cv::imwrite(oss.str(), frame);
	}
}

} /* namespace nokkhum */
