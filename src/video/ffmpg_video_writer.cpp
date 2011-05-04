/*
 * ffmpg_video_writer.cpp
 *
 *  Created on: May 2, 2011
 *      Author: boatkrap
 */

#include "ffmpg_video_writer.hpp"

#include <cstdio>

#include <iostream>
using namespace std;

#define INBUF_SIZE 4096
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

namespace nokkhum {

FfmpgVideoWriter::FfmpgVideoWriter(string directory, string filename,
		int width, int height, int frame_rate) :
	VideoWriter(directory, filename, width, height, frame_rate) {

	/* must be called before using avcodec lib */
	avcodec_init();

	/* register all the codecs */
	avcodec_register_all();

	printf("Video encoding\n");

	c = NULL;
	/* find the mpeg1 video encoder */
	codec = avcodec_find_encoder(CODEC_ID_VP8);
	if (!codec) {
		fprintf(stderr, "codec not found\n");
		exit(1);
	}

	c = avcodec_alloc_context();
	picture = avcodec_alloc_frame();

	/* put sample parameters */
	c->bit_rate = 400000;
	/* resolution must be a multiple of two */
	c->width = 325;
	c->height = 288;
	/* frames per second */
	c->time_base = (AVRational) {1,25};
	c->gop_size = 10; /* emit one intra frame every ten frames */
	c->max_b_frames = 1;
	c->pix_fmt = PIX_FMT_YUV420P;

	/* open it */
	if (avcodec_open(c, codec) < 0) {
		fprintf(stderr, "could not open codec\n");
		exit(1);
	}

	f = fopen(getRecordName().c_str(), "wb");
	if (!f) {
		fprintf(stderr, "could not open %s\n", getRecordName().c_str());
		exit(1);
	}

	/* alloc image and output buffer */
	outbuf_size = 100000;
	outbuf = (uint8_t*) malloc(outbuf_size);
	size = c->width * c->height;
	picture_buf = (uint8_t*) malloc((size * 3) / 2); /* size for YUV 420 */

	picture->data[0] = picture_buf;
	picture->data[1] = picture->data[0] + size;
	picture->data[2] = picture->data[1] + size / 4;
	picture->linesize[0] = c->width;
	picture->linesize[1] = c->width / 2;
	picture->linesize[2] = c->width / 2;

}

FfmpgVideoWriter::~FfmpgVideoWriter() {
	std::cout<<"end writer"<<std::endl;
	/* get the delayed frames */
	for (; out_size; i++) {
		fflush(stdout);

		out_size = avcodec_encode_video(c, outbuf, outbuf_size, NULL);
		printf("write frame %3d (size=%5d)\n", i, out_size);
		fwrite(outbuf, 1, out_size, f);
	}

	/* add sequence end code to have a real mpeg file */
	     outbuf[0] = 0x00;
	     outbuf[1] = 0x00;
	     outbuf[2] = 0x01;
	     outbuf[3] = 0xb7;
	     fwrite(outbuf, 1, 4, f);

	fclose(f);
	free(picture_buf);
	free(outbuf);

	avcodec_close(c);
	av_free(c);
	av_free(picture);
}

void FfmpgVideoWriter::writeFrame(Mat &frame) {

	fflush(stdout);
	/* prepare a dummy image */
	/* Y */
	for (y = 0; y < c->height; y++) {
		for (x = 0; x < c->width; x++) {
			picture->data[0][y * picture->linesize[0] + x] = x + y + i * 3;
		}
	}

	/* Cb and Cr */
	for (y = 0; y < c->height / 2; y++) {
		for (x = 0; x < c->width / 2; x++) {
			picture->data[1][y * picture->linesize[1] + x] = 128 + y + i * 2;
			picture->data[2][y * picture->linesize[2] + x] = 64 + x + i * 5;
		}
	}

	/* encode the image */
	out_size = avcodec_encode_video(c, outbuf, outbuf_size, picture);
	printf("encoding frame %3d (size=%5d)\n", i, out_size);
	fwrite(outbuf, 1, out_size, f);

}

}
