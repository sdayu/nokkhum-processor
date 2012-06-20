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
			// CV_FOURCC('M', 'P', '4', '2'), fps, cv::Size(width, height),
			// CV_FOURCC('X', '2', '6', '4'), fps, cv::Size(width, height),
			// CV_FOURCC('D', 'I', 'V', 'X'), fps, cv::Size(width, height),
			CV_FOURCC('T', 'H', 'E', 'O'), fps, cv::Size(width, height),
			//0, fps, cv::Size(width, height),
			true);
}

CvVideoWriter::~CvVideoWriter() {
	delete record;
	record = nullptr;
}

void CvVideoWriter::open(string filename, string directory, int width,
		int height, int frame_rate) {
	if (record) {
		delete record;
		record = nullptr;
	}
	record = new cv::VideoWriter(getRecordName().c_str(),
			// CV_FOURCC('D', 'I', 'V', 'X'), frame_rate, cv::Size(width, height),
			CV_FOURCC('T', 'H', 'E', 'O'), fps, cv::Size(width, height),
			// CV_FOURCC('D', 'I', 'V', 'X'), fps, cv::Size(width, height),
			true);
}

bool CvVideoWriter::isAvailable(){
	if(record && record->isOpened())
		return true;
	else
		return false;
}

void CvVideoWriter::writeFrame(Mat& frame) {
	(*(record)) << frame;
}

CvVideoWriter& CvVideoWriter::operator <<(Mat& frame) {
	this->writeFrame(frame);
	return *this;
}

}
