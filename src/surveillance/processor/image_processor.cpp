/*
 * image_processor.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "image_processor.hpp"
namespace nokkhum {

ImageProcessor::ImageProcessor(std::string name, ImageQueue &input_image_queue) :
		Job(name), input_image_queue(input_image_queue) {
	this->write_to_output_queue = false;
}

ImageProcessor::~ImageProcessor() {
// TODO Auto-generated destructor stub
}

std::shared_ptr<ImageQueue> ImageProcessor::getNewOutputImageQueue() {
	return this->output_image_queue.getNew();
}

void ImageProcessor::push_to_output_image_queue(nokkhum::Image image){
	for(unsigned long i = 0; i < output_image_queue.getSize(); ++i){
		output_image_queue.get(i)->push(image);
	}
}

}
