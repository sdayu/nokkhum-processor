/*
 * multiple_queue.hpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#ifndef MULTIPLE_QUEUE_HPP_
#define MULTIPLE_QUEUE_HPP_

#include <opencv2/core/core.hpp>
#include "cv_mat_queue.hpp"

namespace nokkhum {

class MultipleMatQueue {
public:
	MultipleMatQueue(int size);
	virtual ~MultipleMatQueue();

	CvMatQueue& get(int index);
	int getSize();

	private:
		int size;
		CvMatQueue *queue_container;
};

}

#endif /* MULTIPLE_QUEUE_HPP_ */
