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
	const std::string& getAudioUri() const;
	void setAudioUri(const std::string& audio_uri);
	const std::string& getVideoUri() const;
	void setVideoUri(const std::string& video_uri);

private:
	int fps;
	std::string video_uri;
	std::string audio_uri;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_MEDIA_RECORDER_ATTRIBUTE_HPP_ */






