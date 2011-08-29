/*
 * cv_mat_queue.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: boatkrap
 */

#include "cv_mat_queue.hpp"

#include <iostream>

namespace nokkhum {

CvMatQueue::CvMatQueue() {
	// TODO Auto-generated constructor stub
//	std::cout<<"construct "<<" this->"<<this <<std::endl;

}

CvMatQueue::~CvMatQueue() {
	// TODO Auto-generated destructor stub
}

void CvMatQueue::push(cv::Mat mat) {
	cv_mat_queue.push(mat);
}

cv::Mat CvMatQueue::pop() {
	cv::Mat mat = cv_mat_queue.front().clone();
	cv_mat_queue.pop();
	return mat;
}

bool CvMatQueue::empty() {
	return cv_mat_queue.empty();
}

int CvMatQueue::size() {
	return cv_mat_queue.size();
}

}
