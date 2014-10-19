/*
 * get_new_killid.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: despair1
 */

#include <pqxx/pqxx>
#include <pqxx/except.hxx>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <set>
using std::cerr;
using std::endl;
using std::cout;
using std::list;
using std::string;
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
	return 0;
}
int get_new_killid1(std::set<string>& new_kills) {
	try {
		std::stringstream s("");
		s<<"dbname=zk";
		pqxx::connection c(s.str());
		cout << "Connected to database." << endl
		         << "Backend version: " << c.server_version() << endl
			 << "Protocol version: " << c.protocol_version() << endl;
		// Begin a transaction acting on our current connection.  Give it a human-
		// readable name so the library can include it in error messages.
		pqxx::work T(c, "test2");
		pqxx::result R( T.exec("SELECT test1.\"id\", analizer_kill.\"killID\"\
				 FROM test1 LEFT OUTER JOIN analizer_kill ON \
				analizer_kill.\"killID\" = test1.\"id\"\
				WHERE analizer_kill.\"killID\" is null") );
		//T.exec("sdf ");
		// Perform a query on the database, storing result tuples in R.
		//pqxx::result R( T.exec("CREATE TABLE test1 (id INTEGER)") );
		//pqxx::tablewriter W(T, "test1");
		// We're expecting to find some tables...
		//if (R.empty()) throw std::logic_error("No tables found!");
		// Process each successive result tuple

		//std::vector<int> MoreData;
		//MoreData.push_back(3);
		    //MoreData.push_back(4);
		    //W.insert(MoreData);
		//std::copy(kills_id.begin(),kills_id.end(), std::back_inserter(W));
		//W.complete();
		//pqxx::result R( T.exec("SELECT * FROM test1 ") );
		for (pqxx::result::const_iterator c1 = R.begin(); c1 != R.end(); ++c1)
		{
		  // Dump tuple number and column 0 value to cout.  Read the value using
		  // as(), which converts the field to the same type as the default value
		  // you give it (or returns the default value if the field is null).
		  cout << '\t' << pqxx::to_string(c1.num()) << '\t' << c1[0].as(std::string())<<
				  "\t"<<c1[1].as(std::string())<< endl;
		  new_kills.insert(c1[0].as(string()));
		}

		// Tell the transaction that it has been successful.  This is not really
		// necessary here, since we didn't make any modifications to the database
		// so there are no changes to commit.
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
	 return 0;
}

int main7() {
	std::set<string> ss;
	//get_new_killid(ss);

	return 0;
}
