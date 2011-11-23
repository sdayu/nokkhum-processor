/*
 * video_surveillance.hpp
 *
 *  Created on: May 3, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_SURVEILLANCE_HPP_
#define NOKKHUM_VIDEO_SURVEILLANCE_HPP_

#include <queue>
#include <vector>
#include <thread>

#include <opencv2/core/core.hpp>

#include "job.hpp"

#include "../config/configuration.hpp"
#include "../config/camera_attribute.hpp"
#include "../config/image_processor_attribute.hpp"


#include "../camera/camera.hpp"

#include "processor/image_processor.hpp"
#include "acquisition/image_acquisition.hpp"


namespace nokkhum {

class VideoSurveillance : public Job {
public:
	VideoSurveillance();
	VideoSurveillance(Configuration &conf);
	virtual ~VideoSurveillance();

	void start();
	void stop();

private:
	CameraAttribute *camera_attribute;
	ImageProcessorAttribute *image_processor_attribute;

	nokkhum::Camera *camera;
	std::vector<ImageProcessor*> image_processor_pool;

	ImageAcquisition *image_acquisition;

	std::vector<std::thread*> thread_pool;
	std::thread acquisiting;

};

}

#endif /* NOKKHUM_VIDEO_SURVEILLANCE_HPP_ */
