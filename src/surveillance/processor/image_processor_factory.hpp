/*
 * image_processor_factory.hpp
 *
 *  Created on: Aug 12, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_

#include <vector>

#include "image_processor.hpp"
#include "../../config/image_processor_attribute.hpp"
#include "../../util/cv_mat_queue.hpp"

namespace nokkhum {

class ImageProcessorFactory {
public:
	ImageProcessorFactory();
	virtual ~ImageProcessorFactory();

	ImageProcessor* getImageProcessor(ImageProcessorAttribute* ipp, CvMatQueue* cv_mat_queue = nullptr);
	std::vector<ImageProcessor*> getImageProcessorPool(ImageProcessorAttribute* ipp, MultipleMatQueue &mmq);

	void getImageProcessorFromVector(std::vector<ImageProcessor*> &image_processor_pool, std::vector<ImageProcessorAttribute*> &ippv, ImageProcessor *parent_image_processor);
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_ */
