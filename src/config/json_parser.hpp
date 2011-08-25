/*
 * json-parser.hpp
 *
 *  Created on: Jul 5, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_JSON_PARSER_HPP_
#define NOKKHUM_JSON_PARSER_HPP_

#include <string>
#include <map>
#include <json_spirit.h>

#include "../surveillance/processor/image_processor.hpp"
#include "../camera/camera.hpp"
#include "image_processor_property.hpp"
#include "camera_property.hpp"

#include "property.hpp"

namespace nokkhum {

typedef std::map<std::string, Property*> PropertyMap;

class JsonParser {
public:
	JsonParser();
	virtual ~JsonParser();

	PropertyMap* parse(std::string file_name);

	CameraProperty* parseCamera(const json_spirit::mObject camera_obj);
	void parseImageProcessor(const json_spirit::mArray image_processor_array, ImageProcessorProperty* ipp);

private:
	const json_spirit::mValue& findValue( const json_spirit::mObject& obj, const std::string& name  );
	const bool findKey( const json_spirit::mObject& obj, const std::string& name  );

	ImageProcessorProperty* parseVideoRecorder(const json_spirit::mObject image_processor_obj);
	ImageProcessorProperty* parseImageRecorder(const json_spirit::mObject image_processor_obj);
	ImageProcessorProperty* parseMotionDetector(const json_spirit::mObject image_processor_obj);
	ImageProcessorProperty* parseFaceDetector(const json_spirit::mObject image_processor_obj);

};

} /* namespace nokkhum */
#endif /* NOKKHUM_JSON_PARSER_HPP_ */
