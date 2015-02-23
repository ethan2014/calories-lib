#include <iostream>

#include "ct.hpp"


void prompt_user() {
	std::string name;
	int sex;
	int age;
	int height_ft;
	int height_in;
	int height_cm;
	int weight_lb;
	int weight_kg;
	int exercise_level;
	int weight_goal;
	float weight_gain_goal;
	float weight_lose_goal;
	int measurement_system;
	std::cout << "-- welcome to calorie tracker --" << std::endl;
	std::cout << "what is your name? ";
	std::getline(std::cin, name);
	std::cout << "sex? ";
	std::cin >> sex;
	std::cout << "age? ";
	std::cin >> age;
	std::cout << "measurement system? ";
	std::cin >> measurement_system;
	std::cout << "exercise level? ";
	std::cin >> exercise_level;
	std::cout << "weight goal? ";
	std::cin >> weight_goal;
	ct::user::set_name(name);
	ct::user::set_measurement_system(measurement_system);
	ct::user::set_age(age);
	ct::user::set_sex(sex);
	ct::user::set_exercise_level(exercise_level);
	ct::user::set_weight_goal(weight_goal);
	
	if (measurement_system == ct::user::imperial) {
		std::cout << "height in feet? ";
		std::cin >> height_ft;
		std::cout << "inches? ";
		std::cin >> height_in;
		std::cout << "weight in pounds? ";
		std::cin >> weight_lb;
		
		if (weight_goal == ct::user::gain_weight) {
			std::cout << "weight gain per week (lb)? ";
			std::cin >> weight_gain_goal;
			ct::user::set_weight_gain_goal(weight_gain_goal);
		} else {
			std::cout << "weight lose per week (lb)? ";
			std::cin >> weight_lose_goal;
			ct::user::set_weight_lose_goal(weight_lose_goal);
		}
		
		ct::user::set_height(height_ft, height_in);
		ct::user::set_weight(weight_lb);
	} else {
		std::cout << "height in cm? ";
		std::cin >> height_cm;
		std::cout << "weight in kg? ";
		std::cin >> weight_kg;
		
		if (weight_goal == ct::user::gain_weight) {
			std::cout << "weight gain per week (kg)? ";
			std::cin >> weight_gain_goal;
			ct::user::set_weight_gain_goal(weight_gain_goal);
		} else {
			std::cout << "weight lose per week (kg)? ";
			std::cin >> weight_lose_goal;
			ct::user::set_weight_lose_goal(weight_lose_goal);
		}
		
		ct::user::set_height(height_cm);
		ct::user::set_weight(weight_kg);
	}
}

int main() {
	ct::init();
	
	if (ct::needs_user_data()) {
		std::cout << "new user" << std::endl;
		prompt_user();
		ct::user::save();
	} else {
		std::cout << "welcome back " << ct::user::name << std::endl;
	}

	try {
		std::cout << "to achieve your goal, you must consume " << ct::user::calculate_calories()
			  << " calories every day" << std::endl;
	} catch (std::string &s) {
		std::cout << s << std::endl;
	}
}
