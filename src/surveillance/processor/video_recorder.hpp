/*
 * video_recorder.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_RECORDER_HPP_
#define NOKKHUM_VIDEO_RECORDER_HPP_

#include <string>
#include <thread>
#include <mutex>

#include <opencv2/core/core.hpp>

#include "image_processor.hpp"
#include "../../video/video_writer.hpp"
#include "../../util/cv_mat_queue.hpp"
#include "../../config/video_recorder_property.hpp"


namespace nokkhum {

class VideoRecorder : public nokkhum::ImageProcessor {
public:
	VideoRecorder(CvMatQueue& input_image_queue);
	VideoRecorder(CvMatQueue& input_image_queue, VideoRecorderProperty* vrp);
	virtual ~VideoRecorder();

	void start();
	void stop();


protected:
	nokkhum::VideoWriter *writer;
	std::string filename;
	std::string directory;
	unsigned int width;
	unsigned int height;
	unsigned int fps;
	unsigned int period;

	std::thread timer;
	std::mutex writer_mutex;


	void getNewVideoWriter();
	void startRecord();
	void startTimer();
	void stopTimer();
	void clock();

};

}

#endif /* NOKKHUM_VIDEO_RECORDER_HPP_ */
