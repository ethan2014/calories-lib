#ifndef CALORIE_TRACKER_HPP
#define CALORIE_TRACKER_HPP

#include <string>

#include "db.hpp"
#include "user.hpp"
#include "meal.hpp"
#include "food.hpp"
#include "day.hpp"

namespace ct {

// this is ugly for now, but its just for testing
const std::string home_dir_name = "../data/calorie_tracker";
const std::string user_file_name = "user_data.txt";

void init();

}

#endif
