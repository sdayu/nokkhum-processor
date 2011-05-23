/*
 * video_recorder.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_RECORDER_HPP_
#define NOKKHUM_VIDEO_RECORDER_HPP_

#include <queue>

#include <opencv/cv.h>

#include "../video/video_writer.hpp"

namespace nokkhum {

class VideoRecorder {
public:
	VideoRecorder(nokkhum::VideoWriter& writer, std::queue<cv::Mat>& image_queue);
	virtual ~VideoRecorder();

	void start();
	void stop();
	void operator()();

private:
	nokkhum::VideoWriter &writer;
	std::queue<cv::Mat> &image_queue;

	bool running;
};

}

#endif /* NOKKHUM_VIDEO_RECORDER_HPP_ */
