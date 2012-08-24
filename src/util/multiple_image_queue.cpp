/*
 * multiple_queue.cpp
 *
 *  Created on: May 10, 2011
 *      Author: boatkrap
 */

#include "multiple_image_queue.hpp"
#include <memory>

namespace nokkhum {

MultipleImageQueue::MultipleImageQueue() {

}

MultipleImageQueue::MultipleImageQueue(int size) {
	for (auto i = 0; i < size; ++i) {
		image_queue_container.push_back(std::make_shared<ImageQueue>());
	}
}

MultipleImageQueue::~MultipleImageQueue() {
	image_queue_container.clear();
}

std::shared_ptr<ImageQueue> MultipleImageQueue::get(int index) {
	return image_queue_container[index];
}

unsigned int MultipleImageQueue::getSize() {
	return image_queue_container.size();
}

std::shared_ptr<ImageQueue> MultipleImageQueue::getNew() {
	std::shared_ptr<ImageQueue> newImageQueue = std::make_shared<ImageQueue>();
	image_queue_container.push_back(newImageQueue);

	return newImageQueue;
}

void MultipleImageQueue::deleteQueue(int index) {
}

}
