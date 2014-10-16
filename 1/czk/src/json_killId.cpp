/*
 * json_killId.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: despair1
 */

#include <iostream>

#include <fstream>
#include <json/json.h>
#include <google/profiler.h>
#include <list>
#include <string>
using std::list;
using std::string;
int get_killid_json(std::ifstream& f,
		list< list<string> >& kills_list) {
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
	for ( unsigned int i =0 ; i<root.size(); i++) {
		list<string> temp_list;
		temp_list.push_back(root[i]["killID"].asString());
		kills_list.push_back(temp_list);
	}
	return 0;
}
int add_killid_2pg(const std::string& conn_name, const list< list <string> >& kills_id ) ;
int main6() {
	ProfilerStart("test2.txt");
	std::ifstream myfile;
	myfile.open("test.txt");
	//myfile<<"wtf?";
	//get_pilot_json("90376921","201407120000",myfile);
	//fclose(fp);
	list< list<string> > l;
	get_killid_json(myfile,l);
	add_killid_2pg("zk",l);
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	for (list<list<string> >::const_iterator i=l.begin();
			i!=l.end();i++) {
		list<string>::const_iterator ii=(*i).begin();
		std::cout<<"tutu :"<<*ii<<std::endl;
	}
	myfile.close();
	ProfilerStop();
	return 0;
}


