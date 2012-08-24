/*
 * multiple_queue.hpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_MULTIPLE_IMAGE_QUEUE_HPP_
#define NOKKHUM_MULTIPLE_IMAGE_QUEUE_HPP_

#include <vector>
#include <memory>

#include <opencv2/core/core.hpp>
#include "image_queue.hpp"

namespace nokkhum {

class MultipleImageQueue {
public:
	MultipleImageQueue(int size);
	MultipleImageQueue();
	virtual ~MultipleImageQueue();

	std::shared_ptr<ImageQueue> get(int index);
	unsigned int getSize();

	std::shared_ptr<ImageQueue> getNew();
	void deleteQueue(int index);

	private:
		std::vector< std::shared_ptr<ImageQueue> > image_queue_container;
};

}

#endif /* NOKKHUM_MULTIPLE_IMAGE_QUEUE_HPP_ */
