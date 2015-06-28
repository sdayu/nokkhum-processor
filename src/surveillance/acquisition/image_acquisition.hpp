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
#include <chrono>
#include <thread>
#include <stdexcept>
#include <memory>
#include <iostream>

#include <opencv2/core/core.hpp>

#include "../../camera/camera.hpp"
#include "../../util/multiple_image_queue.hpp"

#include "../job.hpp"

namespace nokkhum {

class ImageAcquisition : public Job {
public:
	ImageAcquisition(nokkhum::Camera& camera, unsigned int queue_size);
	virtual ~ImageAcquisition();

	void start();
	bool running;
	void stop();

	std::shared_ptr<ImageQueue> getNewOutputImageQueue();
	nokkhum::MultipleImageQueue *getOutputImageQueue();

private:
	nokkhum::MultipleImageQueue multiple_queue;
	nokkhum::Camera &camera;

};

class ImageAcquisitionMonitor {
public:
	ImageAcquisitionMonitor(bool &running, unsigned int &counter, unsigned int time_to_sleep=1000000)
		:running(running), counter(counter), time_to_sleep(time_to_sleep){}
	void operator() (){
		while(running){
			std::this_thread::yield();
			// std::cout<<"time_to_sleep: "<<time_to_sleep<<std::endl;
			std::this_thread::sleep_for(std::chrono::microseconds(time_to_sleep));

			if( counter > 0 ){
				counter = 0;
			}
			else{
				throw std::runtime_error("ImageAcquisition could not get Image");
			}
		}
	}
private:
	bool &running;
	unsigned int &counter;
	unsigned int time_to_sleep; // in milisecound
};

}

#endif /* NOKKHUM_IMAGE_ACQUISITION_HPP_ */
