/*
 * video_recorder.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_RECORDER_HPP_
#define NOKKHUM_VIDEO_RECORDER_HPP_

#include <opencv2/core/core.hpp>

#include "image_processor.hpp"
#include "../../video/video_writer.hpp"
#include "../../util/cv_mat_queue.hpp"


namespace nokkhum {

class VideoRecorder : public nokkhum::ImageProcessor {
public:
	VideoRecorder(nokkhum::VideoWriter& writer, CvMatQueue& input_image_queue);
	virtual ~VideoRecorder();

	void start();

private:
	nokkhum::VideoWriter &writer;

	bool running;
};

}

#endif /* NOKKHUM_VIDEO_RECORDER_HPP_ */
