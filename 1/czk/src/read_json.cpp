/*
 * read_json.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: despair1
 */

#include <sstream>
#include <string>
#include "curl_easy.h"
#include <iostream>
using curl::curl_easy;
int read_json(const std::string& url,
		std::stringstream &s) {
	std::cout<<"begin reading json"<<std::endl;
	curl_writer writer(s);
		    // Pass it to the easy constructor and watch the content returned in that file!
		    curl_easy easy(writer);
		    std::cout<<url<<std::endl;
		    // Add some option to the easy handle
		    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,url) );
		    easy.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));
		    /*curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false );
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1); */
		    easy.add(curl_pair<CURLoption,long>(CURLOPT_SSL_VERIFYPEER, false));
		    easy.add(curl_pair<CURLoption,long>(CURLOPT_SSL_VERIFYHOST, false));
		    try {
		        easy.perform();
		    } catch (curl_easy_exception error) {
		        // If you want to get the entire error stack we can do:
		        vector<pair<string,string> > errors = error.what();
		        // Otherwise we could print the stack like this:
		        error.print_traceback();
		        return 1;
		    }
		    std::cout<<"json reading ok"<<std::endl;
		    //myfile.close();
		    return 0;
}


