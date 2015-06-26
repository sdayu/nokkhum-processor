/*
 * video_writer.cpp
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#include "video_writer.hpp"
#include <iostream>
namespace nokkhum {

VideoWriter::VideoWriter(std::string filename, std::string directory, int width, int height, int fps, std::string extension="ogv") :
	filename(filename), directory(directory), width(width), height(height), fps(fps), extension(extension) {
	this->recordname = directory ;

		if (recordname.at(recordname.length()-1) == '/')
			recordname.append(filename);
		else {
			recordname.append("/");
			recordname.append(filename);
		}
}

VideoWriter::~VideoWriter() {
	// TODO Auto-generated destructor stub
}

std::string VideoWriter::getRecordName() {
	return this->recordname;
}

VideoWriter& VideoWriter::operator <<(cv::Mat& frame) {
	writeFrame(frame);
	return *this;
}

bool VideoWriter::isOpened(){
	return false;
}

}
