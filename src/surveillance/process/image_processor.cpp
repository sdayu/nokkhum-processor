/*
 * image_processor.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "image_processor.hpp"

namespace nokkhum {

ImageProcessor::ImageProcessor(std::string name, CvMatQueue &image_queue):
		Job(name), image_queue(image_queue)
	{
	// TODO Auto-generated constructor stub

}

ImageProcessor::~ImageProcessor() {
	// TODO Auto-generated destructor stub
}

}
