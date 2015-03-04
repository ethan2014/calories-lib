#include "user.hpp"
#include "ct.hpp"

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

namespace ct {
namespace user {

std::string name = "N/A";
int sex = no_answer;
int age = no_answer;
int height_ft = no_answer;
int height_in = no_answer;
int height_cm = no_answer;
int weight_lb = no_answer;
int weight_kg = no_answer;
int calories = no_answer;
int exercise_level = no_answer;
int weight_goal = no_answer;
float weight_gain_goal = no_answer;
float weight_lose_goal = no_answer;
int measurement_system = imperial;

void init() {
	// if the file that stores user data exists, then we just
	// need to load their data from that file
	if (!needs_user_data()) {
		load();
	}
}

bool needs_user_data() {
	return !boost::filesystem::exists(home_dir_name + boost::filesystem::path::preferred_separator +
					  user_file_name);
}

/*
 * setters
 */

void set_name(std::string new_name) {
	if (new_name.size() > max_name_length) {
		throw std::string("error: name is too long");
	}
	
	name = new_name;
}

void set_sex(int new_sex) {
	if (new_sex != no_answer && new_sex != male && new_sex != female) {
		throw std::string("error: invalid sex");
	}

	sex = new_sex;
}

void set_age(int new_age) {
	if (new_age != no_answer && new_age < 0) {
		throw std::string("error: invalid age");
	}

	age = new_age;
}

void set_height(int new_ft, int new_in) {
	if (new_ft != no_answer && new_ft < 0) {
		throw std::string("error: invalid feet value for height");
	}

	if (new_in != no_answer && new_in < 0) {
		throw std::string("error: invalid inch value for height");
	}

	height_ft = new_ft;
	height_in = new_in;
}

void set_height(int new_cm) {
	if (new_cm != no_answer && new_cm < 0) {
		throw std::string("error: invalid centimeter value for height");
	}

	height_cm = new_cm;
}

void set_weight(int new_weight) {
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

void set_calories(int new_calories) {
	if (new_calories != no_answer && new_calories < 0) {
		throw std::string("error: invalid value for calories");
	}
	
	calories = new_calories;
}

void set_exercise_level(int new_level) {
	if (new_level != no_answer && new_level != exercise_none &&
	    new_level != exercise_low && new_level != exercise_med &&
	    new_level != exercise_high && new_level != exercise_very_high) {
		throw std::string("error: invalid value for exercise level");
	}

	exercise_level = new_level;
}

void set_weight_goal(int new_goal) {
	if (new_goal != no_answer && new_goal < 0) {
		throw std::string("error: invalid value for weight goal");
	}

	weight_goal = new_goal;
}

void set_weight_gain_goal(float new_gain) {
	if (new_gain != no_answer && new_gain < 0) {
		throw std::string("error: invalid value for weight gain goal");
	}

	if (weight_goal != gain_weight && new_gain != no_answer) {
		set_weight_goal(gain_weight);
	}

	weight_gain_goal = new_gain;
	weight_lose_goal = no_answer;
}

void set_weight_lose_goal(float new_lose) {
	if (new_lose != no_answer && new_lose < 0) {
		throw std::string("error: invalid value for weight lose goal");
	}

	if (weight_goal != lose_weight && new_lose != no_answer) {
		set_weight_goal(lose_weight);
	}

	weight_gain_goal = no_answer;
	weight_lose_goal = new_lose;
}

void set_measurement_system(int new_system) {
	if (new_system != imperial && new_system != metric) {
		throw std::string("error: invalid value for measurement system");
	}

	measurement_system = new_system;
}

/*
 * IO
 */

void save() {
	std::ofstream out(ct::home_dir_name + boost::filesystem::path::preferred_separator +
			  ct::user_file_name);
	
	out << name << std::endl;
	out << sex << std::endl;
	out << age << std::endl;
	out << height_ft << std::endl;
	out << height_in << std::endl;
	out << height_cm << std::endl;
	out << weight_lb << std::endl;
	out << weight_kg << std::endl;
	out << calories << std::endl;
	out << exercise_level << std::endl;
	out << weight_goal << std::endl;
	out << weight_gain_goal << std::endl;
	out << weight_lose_goal << std::endl;
	out << measurement_system << std::endl;

	out.close();
}

void load() {
	std::ifstream in(ct::home_dir_name + boost::filesystem::path::preferred_separator +
			 ct::user_file_name);
		
	std::getline(in, name);
	in >> sex;
	in >> age;
	in >> height_ft;
	in >> height_in;
	in >> height_cm;
	in >> weight_lb;
	in >> weight_kg;
	in >> calories;
	in >> exercise_level;
	in >> weight_goal;
	in >> weight_gain_goal;
	in >> weight_lose_goal;
	in >> measurement_system;

	in.close();
}

/*
 * calculating calories
 */

int calculate_calories() {
	if (sex == no_answer) {
		throw std::string("error: sex is needed to calculate calories");
	}

	if (age == no_answer) {
		throw std::string("error: age is needed to calculate calories");
	}

	if (height_ft == no_answer && height_in == no_answer && height_cm == no_answer) {
		throw std::string("error: height is needed to calculate calories");
	}

	if (weight_lb == no_answer && weight_kg == no_answer) {
		throw std::string("error: weight is needed to calculate calories");
	}

	if (exercise_level == no_answer) {
		throw std::string("error: exercise level is needed to calculate calories");
	}

	if (weight_goal == no_answer) {
		throw std::string("error: weight goal is needed to calculate calories");
	}

	if (weight_gain_goal == no_answer && weight_lose_goal == no_answer) {
		throw std::string("error: weight gain or lose goal is needed to calculate calories");
	}

	float mass;
	float height;
	float years = age;
	float bmr;
	float tdee;
	float additional_cals;
	float total_cals;

	// we must use metric values for these equations, so convert from imperial
	// if thats what the user is using
	if (measurement_system == metric) {
		mass = weight_kg;
		height = height_cm;
	} else if (measurement_system == imperial) {
		mass = weight_lb_to_kg();
		height = height_ft_to_cm();
	} else {
		throw std::string("error: unkown measurement system");
	}

	//std::cout << "mass: " << mass << std::endl;
	//std::cout << "height: " << height << std::endl;
	//std::cout << "age: " << years << std::endl;

	// calculate the users BMR
	if (sex == male) {
		bmr = (10 * mass) + (6.25 * height) - (5 * years) + 5;
	} else if (sex == female) {
		bmr = (10 * mass) + (6.25 * height) - (5 * years) - 161;
	} else {
		throw std::string("error: unkown sex, must be male or female");
	}

	//std::cout << "bmr: " << bmr << std::endl;

	// calculate TDEE based on exercise level
	if (exercise_level == exercise_none) {
		tdee = bmr * 1.2;
	} else if (exercise_level == exercise_low) {
		tdee = bmr * 1.3;
	} else if (exercise_level == exercise_med) {
		tdee = bmr * 1.55;
	} else if (exercise_level == exercise_high) {
		tdee = bmr * 1.725;
	} else if (exercise_level == exercise_very_high) {
		tdee = bmr * 1.9;
	} else {
		throw std::string("error: unkown exercise level");
	}

	//std::cout << "tdee: " << tdee << std::endl;

	// calculate how many calories this user needs to increase/decrease their
	// TDEE by every day to gain/lose their desired weight
	if (weight_goal == gain_weight) {
		if (measurement_system == metric) {
			additional_cals = weight_gain_goal * calories_per_kg;
		} else {
			additional_cals = weight_gain_goal * calories_per_lb;
		}

		additional_cals /= 7;
		total_cals = tdee + additional_cals;
	} else if (weight_goal == lose_weight) {
		if (measurement_system == metric) {
			additional_cals = weight_lose_goal * calories_per_kg;
		} else {
			additional_cals = weight_lose_goal * calories_per_lb;
		}

		additional_cals /= 7;
		total_cals = tdee - additional_cals;
	} else if (weight_goal == no_goal) {
		total_cals = tdee;
	} else {
		throw std::string("error: unkown weight goal");
	}

	if (total_cals < 0) {
		throw std::string("error: impossible calorie value");
	}

	calories = (int) total_cals;

	return calories;
}

int weight_lb_to_kg() {
	if (weight_lb == no_answer) {
		throw std::string("error: invalid weight in lbs");
	}

	return weight_lb / 2.2;
}

int height_ft_to_cm() {
	if (height_ft == no_answer && height_in == no_answer) {
		throw std::string("error: invalid height in ft and in");
	}

	int total_in = (12 * height_ft) + height_in;

	return total_in * 2.54;
}

}

}
