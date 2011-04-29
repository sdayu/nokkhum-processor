/*
 * video_writer.cpp
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#include "video_writer.hpp"

namespace nokkhum {

VideoWriter::VideoWriter(string filename, string directory, int width, int height, int frame_rate) :
	filename(filename), directory(directory), width(width), height(height), frame_rate(frame_rate) {
	// TODO Auto-generated constructor stub

}

VideoWriter::~VideoWriter() {
	// TODO Auto-generated destructor stub
}

}
