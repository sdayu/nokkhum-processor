/*
 * image_processor.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "image_processor.hpp"

namespace nokkhum {

ImageProcessor::ImageProcessor(std::string name, CvMatQueue &input_image_queue) :
	Job(name), input_image_queue(input_image_queue){
	this->write_to_output_queue = false;
	output_image_queue = NULL;
}

ImageProcessor::ImageProcessor(std::string name, CvMatQueue & input_image_queue, CvMatQueue & out_image_queue) :
	Job(name), input_image_queue(input_image_queue), output_image_queue(&out_image_queue) {
	this->write_to_output_queue = true;
}

ImageProcessor::~ImageProcessor() {
// TODO Auto-generated destructor stub
}

}
