/*
 * job.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "job.hpp"

#include <iostream>

namespace nokkhum {

Job::Job() {
	this->name = "suveillance job";
	this->running = false;
}

Job::Job(std::string name, bool running) :
		name(name), running(running) {

}

Job::~Job() {
	// TODO Auto-generated destructor stub
}

void Job::stop() {
	this->running = false;
}

void Job::operator ()() {
	running = true;
	start();
}

std::string Job::getName() const {
	return name;
}

bool Job::isRunning() const {
	return running;
}

}
