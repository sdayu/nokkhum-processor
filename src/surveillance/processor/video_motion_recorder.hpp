/*
 * video_record_motion.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_MOTION_RECORDER_HPP_
#define NOKKHUM_VIDEO_MOTION_RECORDER_HPP_

#include "video_recorder.hpp"

namespace nokkhum {

class VideoMotionRecorder: public nokkhum::VideoRecorder {
public:
	VideoMotionRecorder(ImageQueue & input_image_queue, VideoRecorderAttribute &vrp);
	virtual ~VideoMotionRecorder();

	void startRecord();

private:
};

} /* namespace nokkhum */
#endif /* NOKKHUM_VIDEO_MOTION_RECORDER_HPP_ */
