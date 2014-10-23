/*
 * add_new_kills.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: despair1
 */


#include <json/json.h>
#include <set>
#include <string>
#include <pqxx/pqxx>
#include <vector>
int add_new_kills(const Json::Value& root,
		const std::set<std::string>& new_kills_id,
		pqxx::tablewriter& kill_table
		//pqxx::tablewriter& attacker_table
		) {
	for ( unsigned int i =0 ; i<root.size(); i++) {
			if ( new_kills_id.count(root[i]["killID"].asString())) {
				/*
 killID          | integer                  | not null
 killTime        | timestamp with time zone | not null
 solarSystemID   | integer                  | not null
 corporationName | character varying(255)   | not null
 characterName   | character varying(255)   | not null
 allianceName    | character varying(255)   | not null
 corporationID   | integer                  | not null
 allianceID      | integer                  | not null
 characterID     | integer                  | not null
				 *
				 */
				//std::cout<<root[i]["killTime"].asString()<<std::endl;
				std::vector<std::string> current_kill;
				std::string killID=root[i]["killID"].asString();
				std::string killTime=root[i]["killTime"].asString();
				current_kill.reserve(9);
				current_kill.push_back(killID);
				current_kill.push_back(killTime);
				current_kill.push_back(root[i]["solarSystemID"].asString());
				current_kill.push_back(root[i]["victim"]["corporationName"].asString());
				current_kill.push_back(root[i]["victim"]["characterName"].asString());
				current_kill.push_back(root[i]["victim"]["allianceName"].asString());
				current_kill.push_back(root[i]["victim"]["corporationID"].asString());
				current_kill.push_back(root[i]["victim"]["allianceID"].asString());
				current_kill.push_back(root[i]["victim"]["characterID"].asString());
				kill_table.insert(current_kill);

				//break;

			}
			//list<string> temp_list;
			//temp_list.push_back(root[i]["killID"].asString());
			//kills_list.push_back(temp_list);
		}
	return 0;
}


