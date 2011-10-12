//============================================================================
// Name        : main.cpp
// Author      : Thanathip Limna
// Version     :
// Copyright   :
// Description : Hello World in C++
//============================================================================
#include <cmath>
#include <ctime>

#include <iostream>
#include <fstream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#include "camera/cv_ip_camera.hpp"
#include "video/cv_video_writer.hpp"
#include "surveillance/video_surveillance.hpp"

int main() {
	cout << "Hello World, Hello Nuk Khum" << endl; // prints Hello World, Hello Nukkhum

	std::string file_name = "config/camera.json";
	std::ifstream ifs(file_name.c_str(), std::ios::in);

	if (!ifs) {
		std::cerr << "file error: " << file_name << std::endl;
		return -1;
	}
	std::ostringstream oss;

	oss << ifs.rdbuf();

	nokkhum::Configuration conf(oss.str());
	ifs.close();

    nokkhum::VideoSurveillance vs(conf);
    vs.start();



    return 0;
}
