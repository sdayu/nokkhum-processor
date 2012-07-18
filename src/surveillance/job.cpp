/*
 * job.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "job.hpp"

#include <iostream>
#include <thread>
#include <glog/logging.h>

namespace nokkhum {

Job::Job() {
	this->name = "suveillance job";
	this->running = false;
}

Job::Job(std::string name, bool running) :
		name(name), running(running) {
	LOG(INFO) << "Construct Job name: " << name;
}

Job::~Job() {
	//std::cout<<"Terminate Job name: "<<getName()<<std::endl;
	LOG(INFO) << "Terminate Job name: "<<getName();
}

void Job::stop() {
	this->running = false;
}

void Job::operator ()() {
	this->running = true;
//	std::cout<<"Call start with operator () status: "<< this->running <<" this-> "<<this<<std::endl;
	LOG(INFO) << "Job Start name: " << name << " thread id: " << std::this_thread::get_id();
	start();
}

std::string Job::getName() const {
	return name;
}

bool Job::isRunning() const {
	return running;
}

}
