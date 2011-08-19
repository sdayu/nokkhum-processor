/*
 * image_processor_factory.hpp
 *
 *  Created on: Aug 12, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_

#include "image_processor.hpp"
#include "../../config/image_processor_property.hpp"
#include "../../util/cv_mat_queue.hpp"

namespace nokkhum {

class ImageProcessorFactory {
public:
	ImageProcessorFactory();
	virtual ~ImageProcessorFactory();

	ImageProcessor* getImageProcessor(ImageProcessorProperty* ipp, CvMatQueue* cv_mat_queue = nullptr);
	void getImageProcessorPool(ImageProcessorProperty* ipp, MultipleMatQueue &mmq);

};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_ */
