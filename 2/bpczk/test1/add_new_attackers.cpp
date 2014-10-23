/*
 * add_new_attackers.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: despair1
 */


#include <json/json.h>
#include <set>
#include <string>
#include <pqxx/pqxx>
#include <vector>
int add_new_attackers(const Json::Value& root,
		const std::set<std::string>& new_kills_id,
		pqxx::tablewriter& attacker_table) {
	for ( unsigned int i =0 ; i<root.size(); i++) {
			if ( new_kills_id.count(root[i]["killID"].asString())) {
				//std::cout<<root[i]["killTime"].asString()<<std::endl;
				//std::vector<std::string> current_kill;
				std::string killID=root[i]["killID"].asString();
				std::string killTime=root[i]["killTime"].asString();

				Json::Value attackers = root[i]["attackers"];
				for ( unsigned int ii=0; ii< attackers.size(); ii++ ) {
					std::vector<std::string> current_attacker;
					//std::cout<<"attacker "<<attackers[ii]["characterName"].asString()<<std::endl;
					current_attacker.reserve(12);
					current_attacker.push_back(attackers[ii]["corporationID"].asString());
					current_attacker.push_back(attackers[ii]["allianceID"].asString());
					current_attacker.push_back(attackers[ii]["characterID"].asString());
					current_attacker.push_back(attackers[ii]["securityStatus"].asString());
					current_attacker.push_back(attackers[ii]["weaponTypeID"].asString());
					current_attacker.push_back(attackers[ii]["finalBlow"].asString());
					current_attacker.push_back(attackers[ii]["shipTypeID"].asString());
					current_attacker.push_back(attackers[ii]["corporationName"].asString());
					current_attacker.push_back(attackers[ii]["characterName"].asString());
					current_attacker.push_back(attackers[ii]["allianceName"].asString());
					current_attacker.push_back(killTime);
					current_attacker.push_back(killID);
					attacker_table.insert(current_attacker);
				}
				//break;
			}
	}
	return 0;
}


