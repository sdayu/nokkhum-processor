/*
 * multiple_queue.cpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#include "multiple_mat_queue.hpp"

namespace nokkhum {

MultipleMatQueue::MultipleMatQueue() {

}

MultipleMatQueue::MultipleMatQueue(int size) {
	for (auto i = 0; i < size; ++i) {
		cvmat_queue_container.push_back(new CvMatQueue());
	}
}

MultipleMatQueue::~MultipleMatQueue() {
	CvMatQueue *tmp = nullptr;
	while (!cvmat_queue_container.empty()) {
			tmp = cvmat_queue_container.back();
			cvmat_queue_container.pop_back();
			delete tmp;
			tmp = nullptr;
		}
}

CvMatQueue & MultipleMatQueue::get(int index) {
	return *cvmat_queue_container[index];
}

int MultipleMatQueue::getSize() {
	return cvmat_queue_container.size();
}

CvMatQueue & MultipleMatQueue::getNew() {
	CvMatQueue *newCvMatQueue = new CvMatQueue();
	cvmat_queue_container.push_back(newCvMatQueue);

	return *newCvMatQueue;
}

void MultipleMatQueue::deleteQueue(int index) {
}

}
