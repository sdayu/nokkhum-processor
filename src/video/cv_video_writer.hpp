/*
 * cv_video_writer.hpp
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CV_VIDEO_WRITER_HPP_
#define NOKKHUM_CV_VIDEO_WRITER_HPP_

#include "video_writer.hpp"

#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace nokkhum {

class CvVideoWriter: public nokkhum::VideoWriter {
public:
	CvVideoWriter();
	CvVideoWriter(std::string filename, std::string directory, int width, int height, int frame_rate, std::string extension);
	virtual ~CvVideoWriter();

	bool open(std::string filename, std::string directory, int width, int height, int frame_rate, std::string extension);
	void release();
	bool isOpened();

	void writeFrame(cv::Mat &frame);

	CvVideoWriter& operator << (cv::Mat& frame);
private:
	cv::VideoWriter record;
};

}

#endif /* NOKKHUM_CV_VIDEO_WRITER_HPP_ */
