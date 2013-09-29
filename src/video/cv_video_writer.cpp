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
		VideoWriter("", 0, 0, 0, 0) {

}

CvVideoWriter::CvVideoWriter(string filename, string directory, int width,
		int height, int fps) :
		VideoWriter(filename, directory, width, height, fps) {

	this->open(filename, directory, width, height, fps);
}

CvVideoWriter::~CvVideoWriter() {
	this->release();
}

bool CvVideoWriter::open(string filename, string directory, int width,
		int height, int fps) {
	if (this->isOpened()) {
		this->release();
	}

	this->filename = filename;
	this->directory = directory;
	this->width	= width;
	this->height = height;
	this->fps = fps;

	record = cv::VideoWriter(getRecordName().c_str(),
			// CV_FOURCC('D', 'I', 'V', 'X'), frame_rate, cv::Size(width, height),
			CV_FOURCC('T', 'H', 'E', 'O'), fps, cv::Size(width, height),
			// CV_FOURCC('D', 'I', 'V', 'X'), fps, cv::Size(width, height),
			true);

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

void CvVideoWriter::writeFrame(Mat& frame) {

	if(frame.size() != cv::Size(width, height)){
		cv::resize(frame, frame, cv::Size(width, height));
	}
	record << frame;
}

CvVideoWriter& CvVideoWriter::operator <<(Mat& frame) {
	this->writeFrame(frame);
	return *this;
}

}
