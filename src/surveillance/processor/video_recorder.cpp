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
#include <exception>

#include <opencv2/highgui/highgui.hpp>
#include <glog/logging.h>

#include "../../video/cv_video_writer.hpp"

#include "../../util/directory_manager.hpp"

#include <sys/time.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>

namespace nokkhum {

VideoRecorder::VideoRecorder(CvMatQueue& input_image_queue) :
		ImageProcessor("VDO Recorder", input_image_queue) {
	this->running = false;
	this->writer = nullptr;

	this->period = 10;
	this->timer = nullptr;

	// std::cout << "Construct video recorder without property" << std::endl;
}

VideoRecorder::VideoRecorder(CvMatQueue & input_image_queue,
		VideoRecorderAttribute *vrp) :
		ImageProcessor(vrp->getName(), input_image_queue) {
	this->running = false;
	this->directory = vrp->getDirectory();
	this->width = vrp->getWidth();
	this->height = vrp->getHeight();
	this->fps = vrp->getFps();
	this->period = 10;
	this->writer = nullptr;
	this->timer = nullptr;
}

VideoRecorder::~VideoRecorder() {
	delete this->writer;
	this->writer = nullptr;

	delete this->timer;
	this->timer = nullptr;
}

void VideoRecorder::start() {
//	LOG(INFO) << "start record";
	this->startRecord();
}

void VideoRecorder::stop() {
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
			<< std::setw(6) << std::setfill('0') << current_time.time_of_day().fractional_seconds() << ".avi";

//	std::string old_name = this->filename.substr (0, this->filename.rfind("-"));
//	std::string new_name = oss.str().substr (0, oss.str().rfind("-"));

//	LOG(INFO)<<"old: "<<old_name;
//	LOG(INFO)<<"new: "<<new_name;

//	if (old_name.compare(new_name) == 0)
//		if(isWriterAvailable()){
//			LOG(INFO)<<"avialable : "<<new_name;
//			return;
//		}

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
		if (this->writer != nullptr && td.total_seconds() < 3) {
//			LOG(INFO) << "less than 3 ";
			return;
		}
	}

	writer_mutex.lock();
	delete this->writer;
	this->writer = nullptr;

	while (this->writer == nullptr) {
		this->writer = new CvVideoWriter(oss.str(), dm.getDirectoryName(),
				this->width, this->height, this->fps);

		if (!this->writer->isAvailable()) {
			delete this->writer;
			this->writer = nullptr;
		}
	}
	writer_mutex.unlock();

	if (this->filename.length() > 0 && this->filename.find("__") != std::string::npos) {
		unsigned int replace_position = this->filename.find("__");
		std::string finish_name = this->filename;
		finish_name.replace(replace_position, replace_position+2, "");
		boost::filesystem::rename(dm.getDirectoryName()+"/"+this->filename, dm.getDirectoryName()+"/"+finish_name);
	}

	this->filename = oss.str();
	LOG(INFO) << "get new video writer name: " << dm.getDirectoryName()
			<< this->filename;

}

void VideoRecorder::startRecord() {

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

		frame = input_image_queue.pop();

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
			nokkhum::DirectoryManager dm(this->directory, "video");
			boost::filesystem::rename(dm.getDirectoryName()+"/"+this->filename, dm.getDirectoryName()+"/"+finish_name);
			this->filename.clear();
	}
	writer_mutex.unlock();
}

void VideoRecorder::startTimer() {
//	LOG(INFO) << "Start Timer";
	// timer = std::thread(&VideoRecorder::clock, this);
	// LOG(INFO) << "Timer RUN";
	this->timer = new RecordTimer(this, this->period);
	this->timer->start();
	// LOG(INFO) << this->getName() << " start Timer";
}

void VideoRecorder::stopTimer() {
	// LOG(INFO) << this->getName() << " stop Timer";
	try {
		if (this->timer != nullptr) {
			this->timer->stop();
			// LOG(INFO) << this->getName() << " delete Timer";
			delete this->timer;
			this->timer = nullptr;
		}
	} catch (std::exception e) {
		LOG(INFO) << "exception in stop timer: " << e.what() << std::endl;
	}
	// LOG(INFO) << this->getName() << " end stop Timer";
}

bool VideoRecorder::isWriterAvailable() {
	bool result = false;
	writer_mutex.lock();
	if (this->writer != nullptr)
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
	if (!this->timer_thred.joinable())
		this->timer_thred.join();

//	LOG(INFO) << "teminate timmer id: "<<this;
}

void RecordTimer::start() {
//	LOG(INFO) << "start Clock";
	if (running){
//		LOG(INFO) << "Clock is available";
		return;
	}
	running = true;//	LOG(INFO) << "Clock end";
	timer_thred = boost::thread(&RecordTimer::clock, this);
	// LOG(INFO) << "end start Clock";
}

void RecordTimer::stop() {
//	LOG(INFO) << "stop Clock";
	running = false;
	timer_thred.interrupt();
//	LOG(INFO) << "end stop Clock";
}

void RecordTimer::clock() {
	// LOG(INFO) << "new Clock :"<<this<<" name: "<<video_recorder->getName()<<" thread id: "<<std::this_thread::get_id();
	while (running) {
//		LOG(INFO) << "Clock working: " << this << " name: "
//				<< video_recorder->getName();
		boost::posix_time::ptime start_time =
				boost::posix_time::microsec_clock::local_time();

//		LOG(INFO) << "Clock working: "<<start_time.time_of_day().minutes()<<" : "<<this->period;
		if (start_time.time_of_day().minutes() % this->period == 0) {
//			LOG(INFO) << "Clock get new writer";
			video_recorder->getNewVideoWriter();
		}
//		else if (!video_recorder->isWriterAvailable()){
//			video_recorder->getNewVideoWriter();
//		}

		boost::posix_time::ptime current_time =
				boost::posix_time::microsec_clock::local_time();

		int sleep_time = (this->period
				- ((this->period + current_time.time_of_day().minutes())
						% this->period)) * 60;

		sleep_time = sleep_time - current_time.time_of_day().seconds();

		if (sleep_time <= 180) {
			// LOG(INFO) << "Clock sleep more time "<<sleep_time<<"s" <<" id: "<<this<<" name: "<<video_recorder->getName();
			sleep_time += (this->period * 60);
		}

		// std::cout << "sleep ---> " << sleep_time << std::endl;
		// LOG(INFO) << "Clock sleep "<<sleep_time<<"s" <<" id: "<<this<<" name: "<<video_recorder->getName();
		boost::posix_time::time_duration sleep_time_d =
				boost::posix_time::seconds(sleep_time);
//		LOG(INFO) << video_recorder->getName() << " sleep time: "<<sleep_time_d;
		boost::this_thread::sleep(sleep_time_d);

	}
//	LOG(INFO) << "Clock end";
}

}
