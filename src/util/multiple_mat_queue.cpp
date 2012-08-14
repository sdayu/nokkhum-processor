/*
 * multiple_queue.cpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#include "multiple_mat_queue.hpp"
#include <memory>

namespace nokkhum {

MultipleMatQueue::MultipleMatQueue() {

}

MultipleMatQueue::MultipleMatQueue(int size) {
	for (auto i = 0; i < size; ++i) {
		cvmat_queue_container.push_back(std::make_shared<CvMatQueue>());
	}
}

MultipleMatQueue::~MultipleMatQueue() {
	cvmat_queue_container.clear();
}

std::shared_ptr<CvMatQueue> MultipleMatQueue::get(int index) {
	return cvmat_queue_container[index];
}

unsigned int MultipleMatQueue::getSize() {
	return cvmat_queue_container.size();
}

std::shared_ptr<CvMatQueue> MultipleMatQueue::getNew() {
	std::shared_ptr<CvMatQueue> newCvMatQueue = std::make_shared<CvMatQueue>();
	cvmat_queue_container.push_back(newCvMatQueue);

	return newCvMatQueue;
}

void MultipleMatQueue::deleteQueue(int index) {
}

}
