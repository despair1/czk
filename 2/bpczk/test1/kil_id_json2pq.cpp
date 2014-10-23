/*
 * kil_id_json2pq.cpp

 *
 *  Created on: Oct 22, 2014
 *      Author: despair1
 */
#include <vector>
#include <string>
#include <json/json.h>
#include <pqxx/pqxx>
#include <iostream>
int kill_id2pg(const Json::Value& root,
		pqxx::work& T) {
	T.exec("CREATE TEMP TABLE test1 (id INTEGER)");
	pqxx::tablewriter temp_table(T, "test1");
	for ( unsigned int i =0 ; i<root.size(); i++) {
			std::vector<std::string> temp_list;
			temp_list.push_back(root[i]["killID"].asString());
			temp_table.insert(temp_list);
			//kills_list.push_back(temp_list);
		}
	std::cout<<"added "<<root.size()<<" entry to temp table"<<std::endl;
	temp_table.complete();
	return 0;

}



