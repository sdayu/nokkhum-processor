/*
 * video_recorder_attribute.hpp
 *
 *  Created on: Jul 25, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_RECORDER_ATTRIBUTE_HPP_
#define NOKKHUM_VIDEO_RECORDER_ATTRIBUTE_HPP_

#include <string>

#include "recorder_attribute.hpp"

namespace nokkhum {

class VideoRecorderAttribute: public RecorderAttribute {
public:
	VideoRecorderAttribute(std::string name, std::string directory, int width,
			int height, int fps);
	VideoRecorderAttribute(std::string name, std::string directory, int width,
			int height, int fps, bool record_motion, int maximum_wait_motion);
	virtual ~VideoRecorderAttribute();
	int getFps() const;
	void setFps(int fps);
	int getMaximumWaitMotion() const;
	bool isRecordMotion() const;

private:
	int fps;
	bool record_motion;
	int maximum_wait_motion;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_VIDEO_RECORDER_ATTRIBUTE_HPP_ */
