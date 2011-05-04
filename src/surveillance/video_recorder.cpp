/*
 * video_recorder.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "video_recorder.hpp"

namespace nokkhum {

VideoRecorder::VideoRecorder(nokkhum::VideoWriter& writer,
		std::queue<cv::Mat>& image_queue) {
	this->image_queue = &image_queue;
	this->writer = & writer;

	this->running = false;
}

VideoRecorder::~VideoRecorder() {
	// TODO Auto-generated destructor stub
}

    void VideoRecorder::start()
    {
    	cv::Mat frame;
    	while(running){
    		frame = this->image_queue->front();
    		*this->writer << frame;
    	}

    }

}
