/*
 * video_recorder.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_RECORDER_HPP_
#define NOKKHUM_VIDEO_RECORDER_HPP_

#include <string>

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


private:
	nokkhum::VideoWriter *writer;
	std::string filename;
	std::string directory;
	unsigned int width;
	unsigned int height;
	unsigned int fps;

};

}

#endif /* NOKKHUM_VIDEO_RECORDER_HPP_ */
