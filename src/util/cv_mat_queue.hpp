/*
 * cv_mat_queue.hpp
 *
 *  Created on: Jun 1, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CV_MAT_QUEUE_HPP_
#define NOKKHUM_CV_MAT_QUEUE_HPP_

#include <queue>
#include <opencv2/core/core.hpp>

namespace nokkhum {

class CvMatQueue {
public:
	CvMatQueue();
	virtual ~CvMatQueue();

	cv::Mat pop();
	void push(cv::Mat);
	bool empty();
	unsigned int size();
private:
	std::queue<cv::Mat> cv_mat_queue;
};

}

#endif /* NOKKHUM_CV_MAT_QUEUE_HPP_ */
