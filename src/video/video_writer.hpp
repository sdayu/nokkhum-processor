/*
 * video_writer.h
 *
 *  Created on: Apr 29, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_WRITER_HPP_
#define NOKKHUM_VIDEO_WRITER_HPP_

#include <string>
using std::string;

#include <opencv2/highgui/highgui.hpp>
using cv::Mat;

namespace nokkhum {

class VideoWriter {
public:
	VideoWriter();
	VideoWriter(string filename, string directory, int width, int height, int fps);
	virtual ~VideoWriter();

	string getRecordName();

	virtual bool open(string filename, string directory, int width, int height, int frame_rate) = 0;
	virtual void release() = 0;
	virtual void writeFrame(Mat &frame) = 0;
	virtual bool isOpened();

	virtual VideoWriter& operator <<(Mat& frame);

protected:
	string filename;
	string directory;
	string recordname;
	int width;
	int height;
	int fps;
};

}

#endif /* NOKKHUM_VIDEO_WRITER_H_ */
