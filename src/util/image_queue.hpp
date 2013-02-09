/*
 * cv_mat_queue.hpp
 *
 *  Created on: Jun 1, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_QUEUE_HPP_
#define NOKKHUM_IMAGE_QUEUE_HPP_

#include <queue>
#include <mutex>
#include <chrono>
#include "../image/image.hpp"

namespace nokkhum {

class ImageQueue {
public:
	ImageQueue();
	virtual ~ImageQueue();

	nokkhum::Image pop();
	void push(nokkhum::Image);
	bool empty();
	unsigned int size();
	bool drop = false;
private:
	std::queue<nokkhum::Image> image_queue;
	std::mutex queue_mutex;
	std::chrono::system_clock::time_point drop_time;
};

}

#endif /* NOKKHUM_IMAGE_QUEUE_HPP_ */
