/*
 * multiple_queue.hpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#ifndef MULTIPLE_QUEUE_HPP_
#define MULTIPLE_QUEUE_HPP_

#include <vector>

#include <opencv2/core/core.hpp>
#include "cv_mat_queue.hpp"

namespace nokkhum {

class MultipleMatQueue {
public:
	MultipleMatQueue(int size);
	MultipleMatQueue();
	virtual ~MultipleMatQueue();

	CvMatQueue* get(int index);
	unsigned int getSize();

	CvMatQueue* getNew();
	void deleteQueue(int index);

	private:
		std::vector<CvMatQueue*> cvmat_queue_container;
};

}

#endif /* MULTIPLE_QUEUE_HPP_ */
