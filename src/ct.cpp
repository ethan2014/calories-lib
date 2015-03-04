#include "ct.hpp"

#include <boost/filesystem.hpp>

namespace ct {

static void check_home_dir() {
	if (boost::filesystem::exists(home_dir_name)) {
		return;
	}

	boost::filesystem::path home(home_dir_name);
	if (!boost::filesystem::create_directory(home)) {
		throw std::string("error: failed to create directory to store local data");
	}
}

void init() {
	// first, make sure the directory where we will store all of
	// our data actually exists
	check_home_dir();

	// then just initialize all the different components of the library,
	// that is pretty much all this file (ct.cpp) is used for, to call
	// all these init()'s so the user doesnt have to do it manually
	ct::user::init();
	ct::day::init();
	ct::meal::init();
	ct::food::init();
}

}
