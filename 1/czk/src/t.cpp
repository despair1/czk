/*
 * t.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: despair1
 */
#include <iostream>

#include <fstream>
#include <json/json.h>
#include <google/profiler.h>

int get_json(std::ifstream& f) {
	Json::Value root;   // will contains the root value after parsing
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( f, root );
	if ( !parsingSuccessful )
	{
	    // report to the user the failure and their locations in the document.
	    std::cout  << "Failed to parse configuration\n"
	               << reader.getFormattedErrorMessages();
	    return 1;
	}
	std::cout<<root.size()<<std::endl;
	return 0;
}

int main() {
	ProfilerStart("test2.txt");
	std::ifstream myfile;
	myfile.open("test.txt");
	//myfile<<"wtf?";
	//get_pilot_json("90376921","201407120000",myfile);
	//fclose(fp);
	get_json(myfile);
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	myfile.close();
	ProfilerStop();
	return 0;
}




