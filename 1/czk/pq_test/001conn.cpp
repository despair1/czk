/*
 * 001conn.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: despair1
 */
#include <pqxx/pqxx>
#include <pqxx/except.hxx>
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;
int test_connection(const std::string& conn_name) {
	try {
		std::stringstream s("");
		s<<"dbname="<<conn_name;
		pqxx::connection c(s.str());
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


int main() {
	cout<<"hello lamerz "<<test_connection("zk")<<endl;
	return 0;
}



