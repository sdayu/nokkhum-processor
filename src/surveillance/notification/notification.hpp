/*
 * notification.hpp
 *
 *  Created on: Jan 22, 2013
 *      Author: superizer
 */

#ifndef NOKKHUM_NOTIFICATION_HPP_
#define NOKKHUM_NOTIFICATION_HPP_

#include <string>
#include "../processor/image_processor.hpp"
#include "../../config/notification_attribute.hpp"

namespace nokkhum{

class Notification : public ImageProcessor {
private:
	int camera_id;
	std::string description;
public:
	Notification(ImageQueue &input_image_queue, NotificationAttribute &nfp, int camera_id);
	virtual ~Notification();
	void start();
	void warning();
};

} /* namespace nokkhum */



#endif /* NOTIFICATION_HPP_ */
