/*
 * camera.h
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_HPP_
#define NOKKHUM_CAMERA_HPP_

#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

namespace nokkhum {

class Camera {
public:
	Camera();
	Camera(int width, int height, int fps);
	virtual ~Camera();

	int getWidth();
	int getHeight();
	int getFps();

	virtual void getImage(cv::Mat& image) = 0;
	Camera& operator >>(cv::Mat& image);

    std::string getModel() const;
    void setModel(std::string model);

    std::string getName() const;
    void setName(std::string name);
private:
	int width;
	int height;
	int fps;
	std::string name;
	std::string model;
};

}

#endif /* NOKKHUM_CAMERA_H_ */
