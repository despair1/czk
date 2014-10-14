/*
 * pgs.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: despair1
 */
#include <pqxx/pqxx>
#include <pqxx/except.hxx>
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;
int create_tbl(const std::string& conn_name) {
	try {
		std::stringstream s("");
		s<<"dbname="<<conn_name;
		pqxx::connection c(s.str());
		cout << "Connected to database." << endl
		         << "Backend version: " << c.server_version() << endl
			 << "Protocol version: " << c.protocol_version() << endl;
		// Begin a transaction acting on our current connection.  Give it a human-
		// readable name so the library can include it in error messages.
		pqxx::work T(c, "test1");

		// Perform a query on the database, storing result tuples in R.
		pqxx::result R( T.exec("CREATE TABLE IF NOT EXISTS test1 (id INTEGER)") );

		// We're expecting to find some tables...
		//if (R.empty()) throw std::logic_error("No tables found!");
		// Process each successive result tuple
		for (pqxx::result::const_iterator c1 = R.begin(); c1 != R.end(); ++c1)
		{
		  // Dump tuple number and column 0 value to cout.  Read the value using
		  // as(), which converts the field to the same type as the default value
		  // you give it (or returns the default value if the field is null).
		  cout << '\t' << pqxx::to_string(c1.num()) << '\t' << c1[0].as(std::string()) << endl;
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




