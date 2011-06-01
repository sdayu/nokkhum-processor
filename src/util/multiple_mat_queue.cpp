/*
 * multiple_queue.cpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#include "multiple_mat_queue.hpp"

namespace nokkhum {

MultipleMatQueue::MultipleMatQueue(int size) :
	size(size) {
	queue_container = new CvMatQueue[size];
}

MultipleMatQueue::~MultipleMatQueue() {
	delete[] queue_container;
	queue_container = NULL;
}

CvMatQueue & MultipleMatQueue::get(int index) {
	return queue_container[index];
}

int MultipleMatQueue::getSize() {
	return this->size;
}

}
