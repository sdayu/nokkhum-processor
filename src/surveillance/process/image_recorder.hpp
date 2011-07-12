/*
 * image-recorder.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_RECORDER_HPP_
#define NOKKHUM_IMAGE_RECORDER_HPP_

#include "image_processor.hpp"

namespace nokkhum {

class ImageRecorder: public nokkhum::ImageProcessor {
public:
	ImageRecorder(CvMatQueue &input_image_queue);
	virtual ~ImageRecorder();

	void start();
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_RECORDER_HPP_ */
