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

#include "../../camera/camera.hpp"
#include "../../util/multiple_mat_queue.hpp"

#include "../job.hpp"

namespace nokkhum {

class ImageAcquisition : public Job {
public:
	ImageAcquisition(nokkhum::Camera& camera, unsigned int queue_size);
	virtual ~ImageAcquisition();

	void start();
	void operator()();
	bool running;
	void stop();

	CvMatQueue *getNewOutputImageQueue();
	nokkhum::MultipleMatQueue *getOutputImageQueue();

private:
	nokkhum::MultipleMatQueue multiple_queue;
	nokkhum::Camera &camera;

};

}

#endif /* NOKKHUM_IMAGE_ACQUISITION_HPP_ */
