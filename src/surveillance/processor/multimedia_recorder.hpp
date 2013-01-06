/*
 * multimedia_recorder.hpp
 *
 *  Created on: Dec 1, 2012
 *      Author: superizer
 */


#ifndef NOKKHUM_MULTIMEDIA_RECORDER_HPP_
#define NOKKHUM_MULTIMEDIA_RECORDER_HPP_

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>
#include <thread>
#include <boost/filesystem.hpp>
#include "image_processor.hpp"
#include "../../config/multimedia_recorder_attribute.hpp"

namespace nokkhum {

class MultimediaRecorder : public nokkhum::ImageProcessor {

public:
	MultimediaRecorder(ImageQueue &input_image_queue, MultimediaRecorderAttribute &mrp);
	void startRecord();
	virtual ~MultimediaRecorder();

	void start();
	void stop();

private:
	std::string directory;
	std::string url;
	std::string command;
	std::string output_name;
	unsigned int width;
	unsigned int height;
	unsigned int fps;
	void getVideo();
	void getAudio();
	void getOutput();



};

}

#endif /* NOKKHUM_MULTIMEDIA_RECORDER_HPP_ */

