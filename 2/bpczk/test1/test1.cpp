#include <boost/python.hpp>
namespace bp=boost::python;

bp::dict dick_f(){
	bp::dict d;
	d["1"]=2;
	d["3"]="hello";
	return d;
}

BOOST_PYTHON_MODULE(test2) {
	bp::def("dick_f",dick_f);
}
