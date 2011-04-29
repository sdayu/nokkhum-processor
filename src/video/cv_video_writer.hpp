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

#include <opencv/highgui.h>
using cv::Mat;

namespace nokkhum {

class CvVideoWriter: public nokkhum::VideoWriter {
public:
	CvVideoWriter(string directory, string filename, int width, int height, int frame_rate);
	virtual ~CvVideoWriter();

	void write_frame(Mat &frame);
private:
	cv::VideoWriter *record;
};

}

#endif /* NOKKHUM_CV_VIDEO_WRITER_HPP_ */
