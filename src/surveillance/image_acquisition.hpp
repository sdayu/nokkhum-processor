/*
 * image_acquisition.hpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_ACQUISITION_HPP_
#define NOKKHUM_IMAGE_ACQUISITION_HPP_

#include <queue>
#include <string>

#include <opencv2/core/core.hpp>

#include "../camera/cv_ip_camera.hpp"
#include "../util/multiple_mat_queue.hpp"

namespace nokkhum {

class ImageAcquisition {
public:
	ImageAcquisition(nokkhum::Camera& camera, MultipleMatQueue& multiple_queue);
	virtual ~ImageAcquisition();

	void start();
	void operator()();
	bool running;
	void stop();
private:
	nokkhum::MultipleMatQueue& multiple_queue;
	nokkhum::Camera &camera;

};

}

#endif /* NOKKHUM_IMAGE_ACQUISITION_HPP_ */
