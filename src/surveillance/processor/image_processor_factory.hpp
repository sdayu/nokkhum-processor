/*
 * image_processor_factory.hpp
 *
 *  Created on: Aug 12, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_

#include <vector>
#include <memory>

#include "image_processor.hpp"
#include "../../config/image_processor_attribute.hpp"
#include "../../util/image_queue.hpp"

namespace nokkhum {

class ImageProcessorFactory {
public:
	ImageProcessorFactory();
	virtual ~ImageProcessorFactory();

	std::shared_ptr<ImageProcessor> getImageProcessor(std::shared_ptr<ImageProcessorAttribute> ipp, ImageQueue &cv_mat_queue);
	std::vector< std::shared_ptr<ImageProcessor> > getImageProcessorPool(std::shared_ptr<ImageProcessorAttribute> ipp, MultipleImageQueue &mmq);

	void getImageProcessorFromVector(std::vector< std::shared_ptr<ImageProcessor> > &image_processor_pool, std::vector< std::shared_ptr<ImageProcessorAttribute> > &ippv, std::shared_ptr<ImageProcessor> parent_image_processor);
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_PROCESSOR_FACTORY_HPP_ */
