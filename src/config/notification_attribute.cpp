/*
 * notification_attribute.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: superizer
 */

#include "notification_attribute.hpp"

namespace nokkhum {

NotificationAttribute::NotificationAttribute(std::string name, std::string type) :
		ImageProcessorAttribute(name), type(type) {

}

NotificationAttribute::~NotificationAttribute() {
	// TODO Auto-generated destructor stub
}

std::string NotificationAttribute::getType() const
  	  {
        return type;
    }


} /* namespace nokkhum */


