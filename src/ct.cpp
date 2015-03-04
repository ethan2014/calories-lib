#include "ct.hpp"

#include <boost/filesystem.hpp>

namespace ct {

void init() {
	check_home_dir();

	ct::db::init();
	ct::user::init();
	ct::day::init();
	ct::meal::init();
	ct::food::init();
}

void check_home_dir() {
	if (boost::filesystem::exists(home_dir_name)) {
		return;
	}

	boost::filesystem::path home(home_dir_name);
	if (!boost::filesystem::create_directory(home)) {
		throw std::string("error: failed to create directory to store local data");
	}
}

}
