/*
 * video_recorder.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "video_recorder.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>
#include <exception>

#include <opencv2/highgui/highgui.hpp>
#include <glog/logging.h>

#include "../../video/cv_video_writer.hpp"

#include "../../util/directory_manager.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>

namespace nokkhum {

VideoRecorder::VideoRecorder(ImageQueue& input_image_queue) :
		ImageProcessor("VDO Recorder", input_image_queue) {
	this->running = false;
	this->writer = nullptr;

	this->period = 10;

	// std::cout << "Construct video recorder without property" << std::endl;
}

VideoRecorder::VideoRecorder(ImageQueue & input_image_queue,
		VideoRecorderAttribute &vrp) :
		ImageProcessor(vrp.getName(), input_image_queue) {
	this->running = false;
	this->directory = vrp.getDirectory();
	this->width = vrp.getWidth();
	this->height = vrp.getHeight();
	this->fps = vrp.getFps();
	this->period = 10;
	this->writer = nullptr;

}

VideoRecorder::~VideoRecorder() {
	this->timer.stop();
	delete this->writer;
	this->writer = nullptr;
}

void VideoRecorder::start() {
	LOG(INFO) << "Start Record";
	this->startRecord();
}

void VideoRecorder::stop() {
	LOG(INFO)<<"Stop Record";
	Job::stop();
	this->stopTimer();
	this->stopRecord();

}

void VideoRecorder::getNewVideoWriter() {

	nokkhum::DirectoryManager dm(this->directory, "video");
	if (!dm.checkAndCreate()) {

	}

	std::ostringstream oss;

	std::string name = this->getName();
	for (unsigned int i = 0; i < name.length(); ++i) {
		if (name.at(i) == ' ')
			name.at(i) = '_';
	}

	boost::posix_time::ptime current_time =
			boost::posix_time::microsec_clock::local_time();

	oss << "__" << name << "-" << current_time.date().year() << "-"
			<< std::setw(2) << std::setfill('0') << (int) current_time.date().month() << "-"
			<< std::setw(2) << std::setfill('0') << current_time.date().day() << "-"
			<< std::setw(2) << std::setfill('0') << current_time.time_of_day().hours() << "-"
			<< std::setw(2) << std::setfill('0') << current_time.time_of_day().minutes() << "-"
			<< std::setw(2) << std::setfill('0') << current_time.time_of_day().seconds() << "-"
			<< std::setw(6) << std::setfill('0') << current_time.time_of_day().fractional_seconds()
			// << ".avi";
			<< ".ogv";

//	std::string old_name = this->filename.substr (0, this->filename.rfind("-"));
//	std::string new_name = oss.str().substr (0, oss.str().rfind("-"));

//	LOG(INFO)<<"old: "<<old_name;
//	LOG(INFO)<<"new: "<<new_name;

//	if (old_name.compare(new_name) == 0)
//		if(isWriterAvailable()){
//			LOG(INFO)<<"avialable : "<<new_name;
//			return;
//		}

	// begin to start new record
	writer_mutex.lock();
	// std::cout<< std::this_thread::get_id() <<"-->: "<<this->filename.length() <<std::endl;

	if (this->filename.length() > 0) {

		std::string old_name = this->filename.substr(this->filename.find("-"),
				this->filename.rfind("-"));

//		LOG(INFO) << "old: " << old_name;
//		LOG(INFO) << "new: " << oss.str();

		for (unsigned long i = 0; i < old_name.length(); i++) {
			if (old_name[i] == '-') {
				old_name[i] = ' ';
			}
			if (old_name[i] == '_') {
				old_name[i] = ' ';
			}
		}

		std::istringstream iss(old_name);
		int day, month, year, hours, minutes, seconds;
		iss >> year >> month >> day >> hours >> minutes >> seconds;
		boost::posix_time::ptime old_time(
				boost::gregorian::date(year, month, day),
				boost::posix_time::time_duration(hours, minutes, seconds));

		boost::posix_time::time_duration td = current_time - old_time;
//		LOG(INFO) << "cur time " << current_time;
//		LOG(INFO) << "old time " << old_time;
//		LOG(INFO) << "td.total_seconds() " << td.total_seconds();
//		std::cout<< "td.total_seconds() " << td.total_seconds()<<std::endl;
		if (this->writer != nullptr && td.total_seconds() < 2) {
//			LOG(INFO) << "less than 3 ";
			return;
		}
	}

	// stop current record before start new record
	this->stopRecord();

	while (this->writer == nullptr) {
		this->writer = new CvVideoWriter(oss.str(), dm.getDirectoryName(),
				this->width, this->height, this->fps);
		if (!this->writer->isOpened()) {
			delete this->writer;
			this->writer = nullptr;
		}
	}

	this->filename = oss.str();

	writer_mutex.unlock();

	LOG(INFO) << "get new video writer name: " << dm.getDirectoryName() << "/"
			<< this->filename;


}

void VideoRecorder::startRecord() {
//	std::cerr<<"getNewVideoWriter"<<std::endl;
	this->getNewVideoWriter();
	this->startTimer();

	cv::Mat frame;
	//	cv::namedWindow("video", 1);

	//	std::cout << "Start record tread/running status: " << runnin//	time_t rawtime;

	//	std::cout<<"runing: "<<this->running<<std::endl;

	//	time(&rawtime);
	//	std::cout<<"start join timer:"<<ctime(&rawtime)<<std::endl;//	LOG(INFO) << "Clock end";
	//this->timer.join();
	//	time(&rawtime);
	//	std::cout<<"start end join timer:"<<ctime(&rawtime)<<std::endl;g << " this-> "
	//			<< this << std::endl;

	while (running) {

		if (input_image_queue.empty()) {
			//			std::cout << "sleep .zZ" << std::endl;
			usleep(1000);
			continue;
		}
//		std::cout << "write to file " << this->filename << std::endl;

		frame = input_image_queue.pop().get();

		//		cv::imshow("video", frame);
		writer_mutex.lock();
		*writer << frame;
		writer_mutex.unlock();

		//		if (cv::waitKey(30) >= 0)
		//			break;
	}
//	std::cout<<"record stop"<<std::endl;
}

void VideoRecorder::stopRecord(){
	if (this->writer == nullptr)
		return;

	writer_mutex.lock();
	delete this->writer;
	this->writer = nullptr;

	if (this->filename.length() > 0 && this->filename.find("__") != std::string::npos) {
			unsigned int replace_position = this->filename.find("__");
			std::string finish_name = this->filename;
			finish_name.replace(replace_position, replace_position+2, "");

			std::string old_name = this->filename.substr(this->filename.find("-"),
							this->filename.rfind("-"));
			for (unsigned long i = 0; i < old_name.length(); i++) {
				if (old_name[i] == '-') {
						old_name[i] = ' ';
				}

				if (old_name[i] == '_') {
						old_name[i] = ' ';
				}
			}

			std::istringstream iss(old_name);
			int day, month, year, hours, minutes, seconds;
			iss >> year >> month >> day >> hours >> minutes >> seconds;
			boost::posix_time::ptime old_time(
				boost::gregorian::date(year, month, day),
					boost::posix_time::time_duration(hours, minutes, seconds));

			nokkhum::DirectoryManager dm(this->directory, "video", old_time);

			std::string full_path_old_file = dm.getDirectoryName()+"/"+this->filename;
			std::string full_path_new_file = dm.getDirectoryName()+"/"+finish_name;

			if (boost::filesystem::exists(full_path_old_file)){
				boost::filesystem::rename(full_path_old_file, full_path_new_file);
			}
			else{
				LOG(INFO) << "video file not found: " << full_path_old_file;
			}

			this->filename.clear();
	}
	writer_mutex.unlock();

}

void VideoRecorder::startTimer() {
//	LOG(INFO) << "Start Timer";
	// timer = std::thread(&VideoRecorder::clock, this);
	// LOG(INFO) << "Timer RUN";
	this->timer = RecordTimer(this, this->period);
	this->timer.start();
	// LOG(INFO) << this->getName() << " start Timer";
}

void VideoRecorder::stopTimer() {
	// LOG(INFO) << this->getName() << " stop Timer";
	try {
		this->timer.stop();
			// LOG(INFO) << this->getName() << " delete Timer";
	} catch (std::exception e) {
		LOG(INFO) << "exception in stop timer: " << e.what() << std::endl;
	}
	// LOG(INFO) << this->getName() << " end stop Timer";
}

bool VideoRecorder::isWriterAvailable() {
	bool result = false;
	writer_mutex.lock();
	if (this->writer != nullptr and this->writer->isOpened())
		result = true;
	else
		result = false;
	writer_mutex.unlock();

	return result;
}

RecordTimer::RecordTimer(VideoRecorder *video_recorder, int period = 10) :
		video_recorder(video_recorder), period(period) {
	running = false;
}

RecordTimer::RecordTimer() {
	running = false;
	video_recorder = nullptr;
	period = 0;
}

RecordTimer::RecordTimer(const RecordTimer& rt) {
	this->running = rt.running;
	this->period = rt.period;
	this->video_recorder = rt.video_recorder;
}

RecordTimer& RecordTimer::operator =(const RecordTimer& rt) {
	this->running = rt.running;
	this->period = rt.period;
	this->video_recorder = rt.video_recorder;

	return *this;
}

RecordTimer::~RecordTimer() {
//	LOG(INFO) << "begin teminate timmer id: "<<this;

	if (this->timer_thred.joinable()){
		this->timer_thred.join();
	}

//	LOG(INFO) << "teminate timmer id: "<<this;
}

void RecordTimer::start() {
//	LOG(INFO) << "start Clock";
	if (running){
//		LOG(INFO) << "Clock is available";
		return;
	}
	running = true;//	LOG(INFO) << "Clock end";
	timer_thred = std::thread(&RecordTimer::clock, this);
	// LOG(INFO) << "end start Clock";
}

void RecordTimer::stop() {
//	LOG(INFO) << "stop Clock";
	running = false;
//	timer_thred.interrupt();
	if (this->timer_thred.joinable()){
		this->timer_thred.join();
	}

//	LOG(INFO) << "end stop Clock";
}

void RecordTimer::clock() {
	const int TIME_TO_SLEEP = 2;

	while (running) {

		auto start_time = std::chrono::system_clock::now();
		auto start_time_t = std::chrono::system_clock::to_time_t(start_time);
		auto start_time_tm = std::localtime(&start_time_t);

		if (start_time_tm->tm_min % this->period == 0) {
			video_recorder->getNewVideoWriter();
		}

		auto sleep_time = start_time.time_since_epoch() + std::chrono::minutes(this->period);
		auto time_fraction = sleep_time % std::chrono::minutes(this->period);

		// std::cout<<"time_fraction: "<< std::chrono::duration_cast<std::chrono::seconds> (time_fraction).count() << "s" << std::endl;
		if (time_fraction > std::chrono::seconds(0)){
			sleep_time -= time_fraction;
		}

		sleep_time -= start_time.time_since_epoch();
		if (sleep_time < std::chrono::seconds(180)) {
			sleep_time += std::chrono::minutes(this->period);
		}

		// LOG(INFO) << "Clock sleep "<<sleep_time<<"s" <<" id: "<<this<<" name: "<<video_recorder->getName();
		// std::cout<<"sleep_time: "<< std::chrono::duration_cast<std::chrono::seconds> (sleep_time).count() << "s" << std::endl;
		std::this_thread::sleep_for(sleep_time%std::chrono::seconds(TIME_TO_SLEEP));
		while (running){
			std::this_thread::sleep_for(std::chrono::seconds(TIME_TO_SLEEP));
			auto current_time = std::chrono::system_clock::now();
			auto diff_time = current_time - start_time;
			// std::cout<<"diff_time: "<< std::chrono::duration_cast<std::chrono::seconds> (diff_time).count() << "s" << std::endl;
			if (diff_time >= sleep_time){
				break;
			}

		}
	}
//	LOG(INFO) << "Clock end";
}

}
