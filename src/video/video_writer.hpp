/*
 * video_writer.h
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_WRITER_HPP_
#define NOKKHUM_VIDEO_WRITER_HPP_

#include <string>

#include <opencv2/opencv.hpp>

namespace nokkhum {

class VideoWriter {
public:
	VideoWriter();
	VideoWriter(std::string filename, std::string directory, int width, int height, int fps, std::string extension);
	virtual ~VideoWriter();

	std::string getRecordName();

	virtual bool open(std::string filename, std::string directory, int width, int height, int fps, std::string extension) = 0;
	virtual void release() = 0;
	virtual void writeFrame(cv::Mat &frame) = 0;
	virtual bool isOpened();

	virtual VideoWriter& operator << (cv::Mat& frame);

protected:
	std::string filename;
	std::string directory;
	std::string recordname;
	std::string extension;
	int width;
	int height;
	int fps;
};

}

#endif /* NOKKHUM_VIDEO_WRITER_H_ */
