/*
 * ffmpg_video_writer.hpp
 *
 *  Created on: May 2, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_FFMPG_VIDEO_WRITER_HPP_
#define NOKKHUM_FFMPG_VIDEO_WRITER_HPP_

#include "video_writer.hpp"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>
}

namespace nokkhum {

class FfmpgVideoWriter: public nokkhum::VideoWriter {
public:
	FfmpgVideoWriter(string directory, string filename, int width, int height,
			int frame_rate);
	virtual ~FfmpgVideoWriter();
	void writeFrame(Mat &frame);

private:
	AVCodec *codec;
	AVCodecContext *c;

	FILE *f;
	AVFrame *picture;
	uint8_t *outbuf, *picture_buf;
	int i, out_size, size, x, y, outbuf_size;
};

}

#endif /* NOKKHUM_FFMPG_VIDEO_WRITER_HPP_ */
