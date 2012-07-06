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
using std::string;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat;

namespace nokkhum {

class CvVideoWriter: public nokkhum::VideoWriter {
public:
	CvVideoWriter();
	CvVideoWriter(string filename, string directory, int width, int height, int frame_rate);
	virtual ~CvVideoWriter();

	bool open(string filename, string directory, int width, int height, int frame_rate);
	void release();
	bool isOpened();

	void writeFrame(Mat &frame);

	CvVideoWriter& operator <<(Mat& frame);
private:
	cv::VideoWriter record;
};

}

#endif /* NOKKHUM_CV_VIDEO_WRITER_HPP_ */
