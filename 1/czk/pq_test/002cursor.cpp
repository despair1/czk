/*
 * 002cursor.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: despair1
 */

#include <pqxx/pqxx>
#include <pqxx/except.hxx>
#include <iostream>
#include <pqxx/cursor>
#include <pqxx/connection>
#include <pqxx/cursor>
#include <pqxx/transaction>
#include <pqxx/result>

using std::cerr;
using std::endl;
using std::cout;
int test_cursor(const std::string& conn_name,
		int BlockSize=1) {
	try {
		std::stringstream s("");
		s<<"dbname="<<conn_name;
		pqxx::connection c(s.str());
		cout << "Connected to database." << endl
		         << "Backend version: " << c.server_version() << endl
			 << "Protocol version: " << c.protocol_version() << endl;
		// Begin a transaction acting on our current connection.  Give it a human-
		// readable name so the library can include it in error messages.
		c.trace(stdout);
		// Begin a transaction acting on our current connection
		    pqxx::transaction<pqxx::serializable> T(c, "test3");

		    // Declare a cursor for the list of database tables
		    //pqxx::stateless_cursor<pqxx::cursor_base::updatepolicy::read_only, pqxx::cursor_base::ownershippolicy::owned> Cur(&T,std::string("SELECT * FROM pg_tables"),std::string("tablecur"), 0);
		    //cout << "Created cursor " << Cur.name() << endl;

		    // If we want to read backwards, move to the last tuple first
		    //if (BlockSize < 0) Cur.move(cursor_base::all());

		    // Stop generating debug output
		    c.trace(0);

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


