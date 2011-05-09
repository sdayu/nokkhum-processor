/*
 * image_acquisition.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef IMAGE_ACQUISITION_HPP_
#define IMAGE_ACQUISITION_HPP_

#include <queue>

#include <opencv/cv.h>

#include "../camera/cv_ip_camera.hpp"

namespace nokkhum {

class ImageAcquisition {
public:
	ImageAcquisition(nokkhum::Camera& camera, std::queue<cv::Mat>& image_queue);
	virtual ~ImageAcquisition();

	void start();
	void operator()();
	bool running;
	void stop();
private:
	std::queue<cv::Mat> &image_queue;
	nokkhum::Camera &camera;
};

}

#endif /* IMAGE_ACQUISITION_HPP_ */
