/*
 * multiple_queue.hpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_MULTIPLE_QUEUE_HPP_
#define NOKKHUM_MULTIPLE_QUEUE_HPP_

#include <vector>
#include <memory>

#include <opencv2/core/core.hpp>
#include "cv_mat_queue.hpp"

namespace nokkhum {

class MultipleMatQueue {
public:
	MultipleMatQueue(int size);
	MultipleMatQueue();
	virtual ~MultipleMatQueue();

	std::shared_ptr<CvMatQueue> get(int index);
	unsigned int getSize();

	std::shared_ptr<CvMatQueue> getNew();
	void deleteQueue(int index);

	private:
		std::vector< std::shared_ptr<CvMatQueue> > cvmat_queue_container;
};

}

#endif /* NOKKHUM_MULTIPLE_QUEUE_HPP_ */
