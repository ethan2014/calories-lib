#ifndef CALORIE_TRACKER_HPP
#define CALORIE_TRACKER_HPP

#include <string>

#include "user_info.hpp"
#include "day.hpp"

namespace ct {

// this is ugly for now, but its just for testing
const std::string home_dir_name = "../data/calorie_tracker";
const std::string user_file_name = "user_data.txt";

void init();
void check_home_dir();

bool needs_user_data();

}

#endif
