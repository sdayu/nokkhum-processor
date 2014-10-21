/*
 * video_recorder.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_NONE_PROCESSOR_HPP_
#define NOKKHUM_NONE_PROCESSOR_HPP_

#include <string>
#include <thread>
#include <mutex>

#include <opencv2/core/core.hpp>

#include "image_processor.hpp"

#include "../../config/none_processor_attribute.hpp"

namespace nokkhum {


class NoneProcessor : public nokkhum::ImageProcessor {
public:
	NoneProcessor(ImageQueue &input_image_queue);
	NoneProcessor(ImageQueue &input_image_queue, NoneProcessorAttribute &npa);
	virtual ~NoneProcessor();

	void start();
	void stop();

protected:
	void popImage();

};

}

#endif /* NOKKHUM_NONE_PROCESSOR_HPP_ */
