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
#include <chrono>
#include <iomanip>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "../../util/directory_manager.hpp"

namespace nokkhum {

ImageRecorder::ImageRecorder(ImageQueue &input_image_queue) :
		ImageProcessor("Image Recorder", input_image_queue), width(320), height(240), directory("/tmp") {
	this->interval = 1;

}

ImageRecorder::ImageRecorder(ImageQueue & input_image_queue,
		ImageRecorderAttribute &irp)  :
		ImageProcessor("Image Recorder", input_image_queue){
	this->width = irp.getWidth();
	this->height = irp.getHeight();
	this->directory = irp.getDirectory();
	this->interval = irp.getInterval();
}

ImageRecorder::~ImageRecorder() {
	// TODO Auto-generated destructor stub
}

void ImageRecorder::start() {
	cv::Mat frame;
	nokkhum::Image image;
	std::chrono::time_point<std::chrono::system_clock> date;
	char buffer[100];
	struct tm * timeinfo;

	unsigned int counter = 0;
	while (running) {
//		std::cout<<"wait to save image"<<std::endl;

		if (input_image_queue.empty()) {
			std::this_thread::sleep_for( std::chrono::microseconds( 1000 ) );
			//std::cout<<"sleep img"<<std::endl;
			continue;
		}
		image = input_image_queue.pop();
		frame = image.get();
		date = image.getDate();


		if(++counter < this->interval){
			continue;
		}
		else{
			counter = 0;
		}

		//boost::posix_time::ptime current_time = boost::posix_time::microsec_clock::local_time();

//		time_t rawtime;
//		time(&rawtime);
//		tm* time_struct = localtime(&rawtime);

		//nokkhum::DirectoryManager dm (this->directory, "image", current_time);
		nokkhum::DirectoryManager dm (this->directory, "image", date);
		if(! dm.checkAndCreate()){
			continue;
		}

		std::string record_name;
		std::ostringstream oss;
		std::time_t tt = std::chrono::system_clock::to_time_t(date);
		timeinfo = localtime(&tt);
		strftime (buffer,80,"%F-%H-%M-%S",timeinfo);

		/*oss << dm.getDirectoryName() << "/"
				<< current_time.date().year() << "-"
				<< std::setw(2) << std::setfill('0') << (int)current_time.date().month() << "-"
				<< std::setw(2) << std::setfill('0') << current_time.date().day() << "-"
				<< std::setw(2) << std::setfill('0') << current_time.time_of_day().hours() << "-"
				<< std::setw(2)	<< std::setfill('0') << current_time.time_of_day().minutes() << "-"
				<< std::setw(2) << std::setfill('0') << current_time.time_of_day().seconds() << "-"
				<< std::setw(6) << std::setfill('0') << current_time.time_of_day().total_microseconds()%1000000
				<< ".png";*/

		 oss << dm.getDirectoryName() << "/" << buffer << "-" << std::setw(6) << std::setfill('0')
		    	<< std::chrono::duration_cast<std::chrono::nanoseconds>(date.time_since_epoch()).count()%1000000
		    	<< ".png";
		cv::imwrite(oss.str(), frame);
//		std::cout<<"save file name: "<<oss.str()<<std::endl;
	}
}

} /* namespace nokkhum */
