/*
 * cv_video_writer.cpp
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#include "cv_video_writer.hpp"
#include <opencv2/opencv.hpp>

namespace nokkhum {

CvVideoWriter::CvVideoWriter() :
		VideoWriter("", 0, 0, 0, 0, "ogv") {

}

CvVideoWriter::CvVideoWriter(std::string filename, std::string directory, int width,
		int height, int fps, std::string extension="ogv") :
		VideoWriter(filename, directory, width, height, fps, extension) {

	this->open(filename, directory, width, height, fps, extension);
}

CvVideoWriter::~CvVideoWriter() {
	this->release();
}

bool CvVideoWriter::open(std::string filename, std::string directory, int width,
		int height, int fps, std::string extension="ogv") {
	if (this->isOpened()) {
		this->release();
	}

	this->filename = filename;
	this->directory = directory;
	this->width	= width;
	this->height = height;
	this->fps = fps;
	this->extension = extension;

	if(extension == "mp4"){
		this->record = cv::VideoWriter(getRecordName().c_str(),
			CV_FOURCC('X', '2', '6', '4'), fps, cv::Size(width, height),
			true);
	}
	else if(extension == "webm"){
		this->record = cv::VideoWriter(getRecordName().c_str(),
			CV_FOURCC('V', 'P', '8', '0'), fps, cv::Size(width, height),
			true);
	}
	else if(extension == "ogv" || extension == "ogg"){
		this->record = cv::VideoWriter(getRecordName().c_str(),
			CV_FOURCC('T', 'H', 'E', 'O'), fps, cv::Size(width, height),
			true);
	}
	else{
		this->record = cv::VideoWriter(getRecordName().c_str(),
			// CV_FOURCC('X', 'V', 'I', 'D'), frame_rate, cv::Size(width, height),
			CV_FOURCC('T', 'H', 'E', 'O'), fps, cv::Size(width, height),
			// CV_FOURCC('D', 'I', 'V', 'X'), fps, cv::Size(width, height),
			// CV_FOURCC('V', 'P', '8', '0'), fps, cv::Size(width, height),
			true);
	}

	return record.isOpened();
}

void CvVideoWriter::release(){
	record.release();
}

bool CvVideoWriter::isOpened(){
	if(record.isOpened())
		return true;
	else
		return false;
}

void CvVideoWriter::writeFrame(cv::Mat& frame) {

	if(frame.size() != cv::Size(width, height)){
		cv::resize(frame, frame, cv::Size(width, height));
	}
	record << frame;
}

CvVideoWriter& CvVideoWriter::operator <<(cv::Mat& frame) {
	this->writeFrame(frame);
	return *this;
}

}
