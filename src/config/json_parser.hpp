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
#include "image_processor_attribute.hpp"
#include "camera_attribute.hpp"

#include "attribute.hpp"

namespace nokkhum {

typedef std::map<std::string, Attribute*> AttributeMap;

class JsonParser {
public:
	JsonParser();
	virtual ~JsonParser();

	AttributeMap* parse(std::string file_name);

	CameraAttribute* parseCamera(const json_spirit::mObject camera_obj);
	void parseImageProcessor(const json_spirit::mArray image_processor_array, ImageProcessorAttribute* ipp);

private:
	const json_spirit::mValue& findValue( const json_spirit::mObject& obj, const std::string& name  );
	const bool findKey( const json_spirit::mObject& obj, const std::string& name  );

	ImageProcessorAttribute* parseVideoRecorder(const json_spirit::mObject image_processor_obj);
	ImageProcessorAttribute* parseImageRecorder(const json_spirit::mObject image_processor_obj);
	ImageProcessorAttribute* parseMotionDetector(const json_spirit::mObject image_processor_obj);
	ImageProcessorAttribute* parseFaceDetector(const json_spirit::mObject image_processor_obj);

};

} /* namespace nokkhum */
#endif /* NOKKHUM_JSON_PARSER_HPP_ */
