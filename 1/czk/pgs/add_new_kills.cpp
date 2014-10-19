/*
 * add_new_kills.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: despair1
 */
#include <json/json.h>
#include <set>
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include <iostream>
#include <fstream>
#include <sstream>
using std::cerr;
using std::endl;
int add_new_attackers(const Json::Value& root,
		const std::set<std::string>& new_kills_id,
		pqxx::tablewriter& attacker_table) {
	for ( unsigned int i =0 ; i<root.size(); i++) {
			if ( new_kills_id.count(root[i]["killID"].asString())) {
				std::cout<<root[i]["killTime"].asString()<<std::endl;
				//std::vector<std::string> current_kill;
				std::string killID=root[i]["killID"].asString();
				std::string killTime=root[i]["killTime"].asString();

				Json::Value attackers = root[i]["attackers"];
				for ( unsigned int ii=0; ii< attackers.size(); ii++ ) {
					std::vector<std::string> current_attacker;
					std::cout<<"attacker "<<attackers[ii]["characterName"].asString()<<std::endl;
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
				std::cout<<root[i]["killTime"].asString()<<std::endl;
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
int get_json(std::stringstream& f,Json::Value& root);
int get_new_killid(pqxx::work& T,std::set<std::string>& new_kills);
int kill_id2pg(const Json::Value& root,
		pqxx::work& T) ;
int read_json(const std::string& url,
		std::stringstream &s);
int main() {
	//ProfilerStart("test2.txt");
	std::stringstream myfile;
	//myfile.open("test.txt");
	read_json("https://zkillboard.com/api/characterID/90376921/startTime/201407120000/",myfile);
	Json::Value root;
	std::set<std::string> new_kills_id;
	try {
		get_json(myfile,root);
		std::stringstream s("");
		s<<"dbname=zk";
		pqxx::connection c(s.str());
		// Begin a transaction acting on our current connection.  Give it a human-
		// readable name so the library can include it in error messages.
		pqxx::work T(c, "test2");
		kill_id2pg(root,T);
		get_new_killid(T,new_kills_id);
		pqxx::tablewriter kill_table(T, "analizer_kill");
		add_new_kills(root,new_kills_id,kill_table);
		kill_table.complete();
		std::vector<std::string> columns;
		columns.push_back("\"corporationID\"");
		columns.push_back("\"allianceID\"");
		columns.push_back("\"characterID\"");
		columns.push_back("\"securityStatus\"");
		columns.push_back("\"weaponTypeID\"");
		columns.push_back("\"finalBlow\"");
		columns.push_back("\"shipTypeID\"");
		columns.push_back("\"corporationName\"");
		columns.push_back("\"characterName\"");
		columns.push_back("\"allianceName\"");
		columns.push_back("\"killTime\"");
		columns.push_back("\"killID_id\"");
		pqxx::tablewriter attacker_table(T,"analizer_attacker",columns.begin(),columns.end());
		add_new_attackers(root,new_kills_id,attacker_table);


		attacker_table.complete();
		T.commit();
	}


		catch (const pqxx::sql_error &e)
		  {
		    // The sql_error exception class gives us some extra information
		    cerr << "SQL error: " << e.what() << endl
		         << "Query was: " << e.query() << endl;
		    return 1;
		  }
		 catch (const std::exception &e)
		  {
		    // All exceptions thrown by libpqxx are derived from std::exception
		    cerr << "Exception: " << e.what() << endl;
		    return 2;
		  }
		 catch (...)
		  {
		    // This is really unexpected (see above)
		    cerr << "Unhandled exception" << endl;
		    return 100;
		  }
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	//myfile.close();
	//ProfilerStop();
	return 0;
}



