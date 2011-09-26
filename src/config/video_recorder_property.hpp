/*
 * video_recorder_property.hpp
 *
 *  Created on: Jul 25, 2011
 *      Author: boatkrap
 */

#ifndef VIDEO_RECORDER_PROPERTY_HPP_
#define VIDEO_RECORDER_PROPERTY_HPP_

#include <string>

#include "recorder_property.hpp"

namespace nokkhum {

class VideoRecorderProperty: public RecorderProperty {
public:
	VideoRecorderProperty(std::string name, std::string directory, int width,
			int height, int fps);
	VideoRecorderProperty(std::string name, std::string directory, int width,
			int height, int fps, bool record_motion, int maximum_wait_motion);
	virtual ~VideoRecorderProperty();
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
#endif /* VIDEO_RECORDER_PROPERTY_HPP_ */
