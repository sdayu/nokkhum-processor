/*
 * multimedia_recorder_attribute.hpp
 *
 *  Created on: Dec 1, 2012
 *      Author: superizer
 */



#ifndef NOKKHUM_MULTIMEDIA_RECORDER_ATTRIBUTE_HPP_
#define NOKKHUM_MULTIMEDIA_RECORDER_ATTRIBUTE_HPP_

#include <string>

#include "video_recorder_attribute.hpp"

namespace nokkhum {

class MultimediaRecorderAttribute: public RecorderAttribute {
public:
//	MultimediaRecorderAttribute();
	MultimediaRecorderAttribute(std::string name, std::string directory, int width, int height, int fps);
	virtual ~MultimediaRecorderAttribute();
	int getFps() const;
	void setFps(int fps);
	const std::string& getAudioUrl() const;
	void setAudioUrl(const std::string& audio_url);
	const std::string& getVideoUrl() const;
	void setVideoUrl(const std::string& video_url);

private:
	int fps;
	std::string video_url;
	std::string audio_url;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_MEDIA_RECORDER_ATTRIBUTE_HPP_ */






