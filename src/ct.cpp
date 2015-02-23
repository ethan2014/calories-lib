#include "ct.hpp"

#include <boost/filesystem.hpp>

#include <fstream>

namespace ct {

void init() {
	check_home_dir();

	if (!needs_user_data()) {
		ct::user::load();
	}
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

bool needs_user_data() {
	return !boost::filesystem::exists(home_dir_name + boost::filesystem::path::preferred_separator +
					  user_file_name);

}

}
