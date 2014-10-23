#include <boost/python.hpp>
namespace bp=boost::python;

bp::dict dick_f(){
	bp::dict d;
	d["1"]=2;
	d["3"]="hello";
	return d;
}
int read_json(const std::string& url,
		std::stringstream &s);
#include <json/json.h>
#include <set>
int get_json(std::stringstream& f,Json::Value& root);
#include <pqxx/pqxx>
int kill_id2pg(const Json::Value& root,
		pqxx::work& T);
int get_new_killid(pqxx::work& T,std::set<std::string>& new_kills);
int add_new_kills(const Json::Value& root,
		const std::set<std::string>& new_kills_id,
		pqxx::tablewriter& kill_table
		//pqxx::tablewriter& attacker_table
		);
int add_new_attackers(const Json::Value& root,
		const std::set<std::string>& new_kills_id,
		pqxx::tablewriter& attacker_table);
using std::cerr;
using std::endl;

bp::dict new_kills_url2pq(const std::string& url) {
	//ProfilerStart("test2.txt");
	bp::dict d;
	d["json"]=0;
	d["new_kills"]=0;
	std::stringstream myfile;
	//myfile.open("test.txt");
	//read_json("https://zkillboard.com/api/characterID/90376921/startTime/201407120000/",myfile);
	read_json(url,myfile);
	Json::Value root;
	std::set<std::string> new_kills_id;
	try {
		get_json(myfile,root);
		d["json"]=root.size();
		std::stringstream s("");
		s<<"dbname=zk";
		pqxx::connection c(s.str());
		// Begin a transaction acting on our current connection.  Give it a human-
		// readable name so the library can include it in error messages.
		pqxx::work T(c, "test2");
		kill_id2pg(root,T);
		get_new_killid(T,new_kills_id);
		d["new_kills"]=new_kills_id.size();
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
		    d["error"]=e.what();
		    d["query"]=e.query();
		    return d;
		  }
		 catch (const std::exception &e)
		  {
		    // All exceptions thrown by libpqxx are derived from std::exception
		    cerr << "Exception: " << e.what() << endl;
		    d["error"]=e.what();
		    return d;
		  }
		 catch (...)
		  {
		    // This is really unexpected (see above)
		    cerr << "Unhandled exception" << endl;
		    d["error"]="unhandled";
		    return d;
		  }
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	//myfile.close();
	//ProfilerStop();
	return d;
}

BOOST_PYTHON_MODULE(test2) {
	//bp::def("dick_f",dick_f);
	//bp::def("new_kills_url2pq",new_kills_url2pq);
	bp::def("tt",new_kills_url2pq);
}
