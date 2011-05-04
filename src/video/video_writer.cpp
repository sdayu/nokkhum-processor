/*
 * video_writer.cpp
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#include "video_writer.hpp"
#include <iostream>
namespace nokkhum {

VideoWriter::VideoWriter(string filename, string directory, int width, int height, int frame_rate) :
	filename(filename), directory(directory), width(width), height(height), frame_rate(frame_rate) {
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

string VideoWriter::getRecordName() {
	return this->recordname;
}

VideoWriter& VideoWriter::operator <<(Mat& frame) {
	writeFrame(frame);
	return *this;
}

}
