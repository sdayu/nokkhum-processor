/* namespace nokkhum */
/*
 * ProcessorBuilderTest.cpp
 *
 *  Created on: Jul 7, 2011
 *      Author: boatkrap
 */

#include "processor_builder.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../../src/config/configuration.hpp"

#include "../../src/camera/cv_ip_camera.hpp"

#include "../../src/surveillance/process/image_processor_factory.hpp"

namespace nokkhum {

ProcessorBuilderTest::ProcessorBuilderTest() {
	// TODO Auto-generated constructor stub

}

ProcessorBuilderTest::~ProcessorBuilderTest() {
	// TODO Auto-generated destructor stub
}

void ProcessorBuilderTest::testProcessorBuilder() {
	
	std::cout << "Hello from json test" << std::endl;

	std::string file_name = "config/camera.json";
	std::ifstream ifs(file_name.c_str(), std::ios::in);

	if (!ifs) {
		std::cerr << "file error: " << file_name << std::endl;
		return;
	}
	std::ostringstream oss;

	oss << ifs.rdbuf();

	nokkhum::Configuration conf(oss.str());
	ifs.close();

	auto cameraProperty = conf.getCameraProperty();
	auto processorProperty = conf.getImageProcessorProperty();
	std::cout << "camera name: " << cameraProperty->getName() << std::endl;

	auto imageProcessorPropertyVector = processorProperty->getImageProcessorPropertyVector();

	for(auto i = 0; i < imageProcessorPropertyVector.size(); i++){
		std::cout<<"Processor name: "<<imageProcessorPropertyVector[i]->getName()<<std::endl;
	}

//	CvIpCamera cvIpCamera(cameraProperty->getWidth(), cameraProperty->getHeight(), cameraProperty->getFps(),
//			cameraProperty->getUsername(), cameraProperty->getPassword());


	MultipleMatQueue mmq(2);
	ImageProcessorFactory ipf;
	ipf.getImageProcessorPool(processorProperty, mmq);

	sleep(1);

}

} /* namespace nokkhum */
