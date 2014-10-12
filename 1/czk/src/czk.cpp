//============================================================================
// Name        : czk.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "curl_easy.h"
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;
using curl::curl_easy;
/* https://zkillboard.com/api/characterID/90376921/startTime/201407120000/ */
int get_pilot_json(const std::string& pilot_id,
		const std::string & start_time, std::ofstream &myfile) {
		std::string s="https://zkillboard.com/api/characterID/";
		s+=pilot_id+"/startTime/"+start_time+"/";

	    //myfile.open ("/Users/Giuseppe/Desktop/test.txt");
	    // Create a writer to handle the stream

	    curl_writer writer(myfile);
	    // Pass it to the easy constructor and watch the content returned in that file!
	    curl_easy easy(writer);
	    std::cout<<s<<std::endl;
	    // Add some option to the easy handle
	    easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,s) );
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
	    }
	    //myfile.close();
	    return 0;
}


int main1() {
	std::ofstream myfile;
	myfile.open("test.txt");
	//myfile<<"wtf?";
	get_pilot_json("90376921","201407120000",myfile);
	//fclose(fp);
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	myfile.close();
	return 0;
}
