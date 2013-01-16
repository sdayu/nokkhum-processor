/*
 * multimedia_recorder.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: superizer
 */

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "multimedia_recorder.hpp"

namespace nokkhum {
MultimediaRecorder::MultimediaRecorder(ImageQueue &input_image_queue,
		MultimediaRecorderAttribute &mrp) :
		ImageProcessor("Multimedia Recorder", input_image_queue) {
	this->running = false;
	this->directory = mrp.getDirectory();
	this->width = mrp.getWidth();
	this->height = mrp.getHeight();
	this->url = mrp.getUrl();
	this->fps = mrp.getFps();
	this->record_hour = 0;
	this->record_minute = 0;
	this->record_sec = 10;
	//this->period = 10;
}
MultimediaRecorder::~MultimediaRecorder() {

}
void MultimediaRecorder::startRecord() {
	this->running = true;
	std::vector<std::thread> thread_vector;

	while (this->running) {
		//TODO create directory
		boost::filesystem::create_directories(this->directory);

		//TODO create output_name
		std::ostringstream oss;
		std::chrono::time_point < std::chrono::system_clock > now;
		now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto micro = std::chrono::duration_cast < std::chrono::microseconds
				> (duration).count();
		std::time_t time = std::chrono::system_clock::to_time_t(now);
		struct tm* tm = localtime(&time);
		oss << "Multimedia_Recorder-" << std::to_string(tm->tm_year + 1900)
				<< "-" << std::setw(2) << std::setfill('0')
				<< std::to_string(tm->tm_mon + 1) << "-" << std::setw(2)
				<< std::setfill('0') << std::to_string(tm->tm_mday) << "-"
				<< std::setw(2) << std::setfill('0')
				<< std::to_string(tm->tm_hour) << "-" << std::setw(2)
				<< std::setfill('0') << std::to_string(tm->tm_min) << "-"
				<< std::setw(2) << std::setfill('0')
				<< std::to_string(tm->tm_sec) << "-" << std::setw(6)
				<< std::setfill('0') << std::to_string(micro % 1000000);

		this->output_name = oss.str();

		command = "cd " + this->directory;
		system(command.c_str());

		std::thread audio(&MultimediaRecorder::getAudio, this);
		std::thread video(&MultimediaRecorder::getVideo, this);

		for (auto it = thread_vector.begin();
				it != thread_vector.end() && !thread_vector.empty(); ++it) {
			if (it->joinable()) { // if thread die join and remove
				it->join();
				thread_vector.erase(it);
			}
		}

		video.join();
		audio.join();

		std::thread output(&MultimediaRecorder::getOutput, this,
				this->output_name);
		//	thread_vector.push_back(&MultimediaRecorder::getOutput, this, this->output_name);

		thread_vector.push_back(std::move(output));

	}
	for (auto it = thread_vector.begin(); it != thread_vector.end(); ++it) {
		it->join();
	}
	thread_vector.clear();
	//std::cout << "recording finish :D " << std::endl;
}
void MultimediaRecorder::getVideo() {
	//system("ffmpeg -r 15 -i http://admin:123zxc@172.30.235.183/video/mjpg.cgi?.mjpg  -s 640x480 -t 00:00:10 -vcodec libtheora -r 15 video.ogv");
	command = "ffmpeg -r " + std::to_string(this->fps) + " -i " + this->url
			+ "/video/mjpg.cgi?.mjpg -s " + std::to_string(this->width) + "x"
			+ std::to_string(this->height) + " -t "
			+ std::to_string(this->record_hour) + ":"
			+ std::to_string(this->record_minute) + ":"
			+ std::to_string(this->record_sec) + " -vcodec libtheora -r "
			+ std::to_string(this->fps) + " " + this->directory + "/__"
			+ this->output_name + "-video.ogv 2> /dev/null";
	system(command.c_str());
}
void MultimediaRecorder::getAudio() {
	command = "ffmpeg -i " + this->url + "/audio.cgi -t "
			+ std::to_string(this->record_hour) + ":"
			+ std::to_string(this->record_minute) + ":"
			+ std::to_string(this->record_sec) + " " + this->directory + "/__"
			+ this->output_name + "-audio.ogg 2> /dev/null";
	system(command.c_str());
}
void MultimediaRecorder::getOutput(std::string output) {
	command = "ffmpeg -i " + this->directory + "/__" + output + "-video.ogv -i "
			+ this->directory + "/__" + output + "-audio.ogg -r "
			+ std::to_string(this->fps) + " " + this->directory + "/" + output
			+ ".ogv 2> /dev/null";
	system(command.c_str());
	//system("ffmpeg -i video.ogv -i audio.ogg -r 15 output.ogv");
	command = "rm " + this->directory + "/__" + output + "-video.ogv "
			+ this->directory + "/__" + output + "-audio.ogg";
	system(command.c_str());
	//command = "mv " + this->directory + "/" + this->output_name + "__output.ogv " + this->directory + "/" + this->output_name + ".ogv";
	//system(command.c_str());
}

void MultimediaRecorder::start() {
	this->startRecord();
}

void MultimediaRecorder::stop() {
	Job::stop();
}

}

