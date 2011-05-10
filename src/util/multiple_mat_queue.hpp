/*
 * multiple_queue.hpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#ifndef MULTIPLE_QUEUE_HPP_
#define MULTIPLE_QUEUE_HPP_

#include <queue>
#include <opencv/cv.h>

namespace nokkhum {

class MultipleMatQueue {
public:
	MultipleMatQueue(int size);
	virtual ~MultipleMatQueue();

	std::queue<cv::Mat>& get(int index);
	int getSize();

	private:
		int size;
		std::queue<cv::Mat> *queue_container;
};

}

#endif /* MULTIPLE_QUEUE_HPP_ */
