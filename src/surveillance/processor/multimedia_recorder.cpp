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
#include <set>
#include <Poco/Process.h>
#include <Poco/PipeStream.h>
#include <Poco/StreamCopier.h>
#include <fstream>


#include "multimedia_recorder.hpp"
using Poco::Process;
using Poco::ProcessHandle;

namespace nokkhum {
MultimediaRecorder::MultimediaRecorder(ImageQueue &input_image_queue,
		MultimediaRecorderAttribute &mrp) :
		ImageProcessor("Multimedia Recorder", input_image_queue) {
	this->running = false;
	this->directory = mrp.getDirectory();
	this->width = mrp.getWidth();
	this->height = mrp.getHeight();
	this->video_uri = mrp.getVideoUri();
	this->audio_uri = mrp.getAudioUri();
	this->fps = mrp.getFps();
	this->record_hour = 0;
	this->record_minute = 0;
	this->record_sec = 30;
	//this->period = 10;
}
MultimediaRecorder::~MultimediaRecorder() {

}
void MultimediaRecorder::startRecord() {
	this->running = true;
	std::vector<std::thread> thread_vector;

	while (this->running) {

		nokkhum::DirectoryManager dm (this->directory, "multimedia");
							if(! dm.checkAndCreate()){
								continue;
							}
		this->dt = dm.getDirectoryName();

		//TODO create directory
		//boost::filesystem::create_directories(this->directory + "/multimedia/");
		//boost::posix_time::ptime current_time = boost::posix_time::microsec_clock::local_time();

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

		//command = "cd " + this->directory;
		//system(command.c_str());

		std::thread audio(&MultimediaRecorder::getAudio, this);
		std::thread video(&MultimediaRecorder::getVideo, this);

		/*std::set<int>::iterator it;
		std::cout << "process : ";
		for(it=this->process.begin(); it!=this->process.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';*/

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
	std::cout << "clear :)" << std::endl;
	thread_vector.clear();
	//std::cout << "recording finish :D " << std::endl;
}
void MultimediaRecorder::getVideo() {
	//system("ffmpeg -r 15 -i http://admin:123zxc@172.30.235.183/video/mjpg.cgi?.mjpg  -s 640x480 -t 00:00:10 -vcodec libtheora -r 15 video.ogv");
	/*command = "ffmpeg -r " + std::to_string(this->fps) + " -i " + this->url
			+ "/video/mjpg.cgi?.mjpg -s " + std::to_string(this->width) + "x"
			+ this->setString(this->height) + " -t "
			+ this->setString(this->record_hour) + ":"
			+ this->setString(this->record_minute) + ":"
			+ this->setString(this->record_sec) + " -r "
			+ this->setString(this->fps) + " " + this->dt + "/__"
			+ this->output_name + "-video.webm 2> /dev/null";
	system(command.c_str());*/
	std::string cmd("avconv");
	std::vector<std::string> args;
	args.push_back("-r");
	args.push_back(std::to_string(this->fps));
	args.push_back("-i");
	//args.push_back(this->url + "/video/mjpg.cgi?.mjpg");
	//std::cout << this->video_uri << std::endl;
	args.push_back(this->video_uri);
	args.push_back("-s");
	args.push_back(std::to_string(this->width) + "x" + this->setString(this->height));
	args.push_back("-t");
	args.push_back(this->setString(this->record_hour) + ":"
				+ this->setString(this->record_minute) + ":"
				+ this->setString(this->record_sec));
	args.push_back("-r");
	args.push_back(this->setString(this->fps));
	args.push_back(this->dt + "/__"
			+ this->output_name + "-video.webm");
	Poco::Pipe outPipe;
	Poco::Pipe errPipe;
	ProcessHandle ph = Process::launch(cmd, args, 0, &outPipe, &errPipe);
	//std::cout << "process id: "<< ph.id() << std::endl;
	this->process.insert(ph.id());
	ph.wait();
	this->process.erase(ph.id());

}
void MultimediaRecorder::getAudio() {
	/*command = "ffmpeg -i " + this->url + "/audio.cgi -t "
			+ this->setString(this->record_hour) + ":"
			+ this->setString(this->record_minute) + ":"
			+ this->setString(this->record_sec) + " " + this->dt + "/__"
			+ this->output_name + "-audio.webm 2> /dev/null";
	system(command.c_str());*/
	std::string cmd("avconv");
	std::vector<std::string> args;
	args.push_back("-i");
	//args.push_back(this->url + "/audio.cgi");
	args.push_back(this->audio_uri);
	args.push_back("-t");
	args.push_back(this->setString(this->record_hour) + ":"
			+ this->setString(this->record_minute) + ":"
			+ this->setString(this->record_sec));
	args.push_back(this->dt + "/__"
			+ this->output_name + "-audio.webm");
	Poco::Pipe outPipe;
	Poco::Pipe errPipe;
	ProcessHandle ph = Process::launch(cmd, args, 0, &outPipe, &errPipe);
	//std::cout << "process id: "<< ph.id() << std::endl;
	this->process.insert(ph.id());
	ph.wait();
	this->process.erase(ph.id());

}
void MultimediaRecorder::getOutput(std::string output) {
	command = "avconv -i " + this->dt + "/__" + output + "-video.webm -i "
			+ this->dt + "/__" + output + "-audio.webm -r "
			+ std::to_string(this->fps) + " " + this->dt+ "/__" + output
			+ ".webm 2> /dev/null";
	system(command.c_str());
	/*std::string cmd("avconv");
	std::vector<std::string> args;
	args.push_back("-i");
	args.push_back(this->dt + "/__" + output + "-video.webm");
	args.push_back("-i");
	args.push_back(this->dt + "/__" + output + "-audio.webm");
	args.push_back("-r");
	args.push_back(std::to_string(this->fps));
	args.push_back(this->dt+ "/__" + output
			+ ".webm");
	Poco::Pipe outPipe;
	Poco::Pipe errPipe;
	ProcessHandle ph = Process::launch(cmd, args, 0, &outPipe, &errPipe);
	//std::cout << "process id: "<< ph.id() << std::endl;
	ph.wait();*/

	command = "mv " + this->dt + "/__" + output + ".webm " + this->dt + "/" + output + ".webm";
	system(command.c_str());
	//system("ffmpeg -i video.ogv -i audio.ogg -r 15 output.ogv");
	command = "rm " + this->dt + "/__" + output + "-video.webm "
			+ this->dt + "/__" + output + "-audio.webm";
	system(command.c_str());
	/*std::string cmd2("mv");
	std::vector<std::string> args2;
	args2.push_back(this->dt + "/__" + output + ".webm");
	args2.push_back(this->dt + "/" + output + ".webm");
	Poco::Pipe outPipe2;
	Poco::Pipe errPipe2;
	ProcessHandle ph2 = Process::launch(cmd2, args2, 0, &outPipe2, &errPipe2);
	//std::cout << "process id: "<< ph.id() << std::endl;
	ph2.wait();*/
	//command = "mv " + this->directory + "/" + this->output_name + "__output.ogv " + this->directory + "/" + this->output_name + ".ogv";
	//system(command.c_str());
}

void MultimediaRecorder::start() {
	this->startRecord();
}

void MultimediaRecorder::stop() {
	Job::stop();
	command = "kill -KILL";
	std::set<int>::iterator it;
	for (it=this->process.begin(); it!=this->process.end(); ++it)
	    //std::cout << ' ' << *it;
		command += " " +std::to_string(*it);
	//std::cout << command << std::endl;
	system(command.c_str());
	this->process.clear();
}

std::string MultimediaRecorder::setString(int num){
	if(num < 10) return "0" + std::to_string(num);
	return std::to_string(num);
}

}

