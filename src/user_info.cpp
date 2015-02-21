#include "user_info.hpp"

namespace ct {

UserInfo::UserInfo() {
	set_name("N/A");
	set_sex(no_answer);
	set_age(no_answer);
	set_height(no_answer, no_answer); // imperial 
	set_height(no_answer); // metric
	set_weight(no_answer);
	set_calories(no_answer);
	set_exercise_level(no_answer);
	set_weight_goal(no_answer);
	set_weight_gain_goal(no_answer);
	set_weight_lose_goal(no_answer);
	set_measurement_system(imperial);
}

/*
 * setters
 */

void UserInfo::set_name(std::string new_name) {
	name = new_name;
}

void UserInfo::set_sex(int new_sex) {
	if (new_sex != no_answer && new_sex != male && new_sex != female) {
		throw std::string("error: invalid sex");
	}

	sex = new_sex;
}

void UserInfo::set_age(int new_age) {
	if (new_age != no_answer && new_age < 0) {
		throw std::string("error: invalid age");
	}

	age = new_age;
}

void UserInfo::set_height(int new_ft, int new_in) {
	if (new_ft != no_answer && new_ft < 0) {
		throw std::string("error: invalid feet value for height");
	}

	if (new_in != no_answer && new_in < 0) {
		throw std::string("error: invalid inch value for height");
	}

	height_ft = new_ft;
	height_in = new_in;
}

void UserInfo::set_height(int new_cm) {
	if (new_cm != no_answer && new_cm < 0) {
		throw std::string("error: invalid centimeter value for height");
	}

	height_cm = new_cm;
}

void UserInfo::set_wieght(int new_weight) {
	if (new_weight != no_answer && new_weight < 0) {
		throw std::string("error: invalid value for weight");
	}

	if (new_weight == no_answer) {
		weight_lb = new_weight;
		weight_kg = new_weight;
	} else if (measurement_system == imperial) {
		weight_lb = new_weight;
	} else if (measurement_system == metric) {
		weight_kg = new_weight;
	} else {
		throw std::string("error: unkown measurement system");
	}
}

void UserInfo::set_calories(int new_calories) {
	if (new_calories != no_answer && new_calories < 0) {
		throw std::string("error: invalid value for calories");
	}
	
	calories = new_calories;
}

void UserInfo::set_exercise_level(int new_level) {
	if (new_level != no_answer && new_level != exercise_none &&
	    new_level != exercise_low && new_level != exercise_med &&
	    new_level != exercise_high && new_level != exercise_very_high) {
		throw std::string("error: invalid value for exercise level");
	}

	exercise_level = new_level;
}

void UserInfo::set_weight_goal(int new_goal) {
	if (new_goal != no_answer && new_goal < 0) {
		throw std::string("error: invalid value for weight goal");
	}

	weight_goal = new_goal;
}

void UserInfo::set_weight_gain_goal(int new_gain) {
	if (new_gain != no_answer && new_gain < 0) {
		throw std::string("error: invalid value for weight gain goal");
	}

	if (weight_goal != gain_weight && new_gain != no_answer) {
		set_weight_goal(gain_weight);
	}

	weight_gain_goal = new_gain;
	weight_lose_goal = no_answer;
}

void UserInfo::set_weight_lose_goal(int new_lose) {
	if (new_lose != no_answer && new_lose < 0) {
		throw std::string("error: invalid value for weight lose goal");
	}

	if (weight_goal != lose_weight && new_lose != no_answer) {
		set_weight_goal(lose_weight);
	}

	weight_gain_goal = no_answer;
	weight_lose_goal = new_lose;
}

void UserInfo::set_measurement_system(int new_system) {
	if (new_system != imperial && new_system != metric) {
		throw std::string("error: invalid value for measurement system");
	}

	measurement_system = new_system;
}

/*
 * getters
 */

/*
 * IO
 */



}
