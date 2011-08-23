/*
 * cv_video_writer.cpp
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#include "cv_video_writer.hpp"

namespace nokkhum {

CvVideoWriter::CvVideoWriter() :
		VideoWriter("", 0, 0, 0, 0) {
	this->record = nullptr;
}

CvVideoWriter::CvVideoWriter(string filename, string directory, int width,
		int height, int fps) :
		VideoWriter(filename, directory, width, height, fps) {

	record = new cv::VideoWriter(getRecordName().c_str(),
			CV_FOURCC('D', 'I', 'V', 'X'), fps, cv::Size(width, height),
			//0, fps, cv::Size(width, height),
			true);
}

CvVideoWriter::~CvVideoWriter() {
	delete record;
	record = NULL;
}

void CvVideoWriter::open(string filename, string directory, int width,
		int height, int frame_rate) {
	record = new cv::VideoWriter(getRecordName().c_str(),
			CV_FOURCC('D', 'I', 'V', 'X'), frame_rate, cv::Size(width, height),
			//0, fps, cv::Size(width, height),
			true);
}

void CvVideoWriter::writeFrame(Mat& frame) {
	(*(record)) << frame;
}

CvVideoWriter& CvVideoWriter::operator <<(Mat& frame) {
	this->writeFrame(frame);
	return *this;
}

}
