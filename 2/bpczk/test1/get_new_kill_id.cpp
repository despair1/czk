/*
 * get_new_kill_id.cpp

 *
 *  Created on: Oct 22, 2014
 *      Author: despair1
 */

#include <pqxx/pqxx>
#include <string>
#include <set>
using std::string;
#include <iostream>
int get_new_killid(pqxx::work& T,std::set<string>& new_kills) {

	pqxx::result R( T.exec("SELECT test1.\"id\", analizer_kill.\"killID\"\
					 FROM test1 LEFT OUTER JOIN analizer_kill ON \
					analizer_kill.\"killID\" = test1.\"id\"\
					WHERE analizer_kill.\"killID\" is null") );
	for (pqxx::result::const_iterator c1 = R.begin(); c1 != R.end(); ++c1)
			{
			  // Dump tuple number and column 0 value to cout.  Read the value using
			  // as(), which converts the field to the same type as the default value
			  // you give it (or returns the default value if the field is null).
			  //cout << '\t' << pqxx::to_string(c1.num()) << '\t' << c1[0].as(std::string())<<
				//	  "\t"<<c1[1].as(std::string())<< endl;
			  new_kills.insert(c1[0].as(string()));
			}
	std::cout<<" founded "<<new_kills.size()<<" new entry"<<std::endl;
	return 0;
}


