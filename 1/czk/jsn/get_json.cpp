/*
 * get_json.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: despair1
 */

#include <json/json.h>
#include <iostream>
#include <fstream>

int get_json(std::ifstream& f,Json::Value& root) {
	Json::Reader reader;
	//Json::Value root1;
	bool parsingSuccessful = reader.parse( f, root );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n"
				   << reader.getFormattedErrorMessages();
		throw std::logic_error("Failed to parse configuration 111!\n");
		return 1;
	}
	return 0;
}
