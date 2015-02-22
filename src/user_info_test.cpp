#include <iostream>

#include "user_info.hpp"

void prompt_user(ct::UserInfo &user) {
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
	std::cout << "enter -1 for any field if you don't want it stored" << std::endl;
	std::cout << "all fields are optional" << std::endl;
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

	user.set_name(name);
	user.set_measurement_system(measurement_system);
	user.set_age(age);
	user.set_sex(sex);
	user.set_exercise_level(exercise_level);
	user.set_weight_goal(weight_goal);

	if (measurement_system == ct::imperial) {
		std::cout << "height in feet? ";
		std::cin >> height_ft;
		std::cout << "inches? ";
		std::cin >> height_in;
		std::cout << "weight in pounds? ";
		std::cin >> weight_lb;

		if (weight_goal == ct::gain_weight) {
			std::cout << "weight gain per week (lb)? ";
			std::cin >> weight_gain_goal;
			user.set_weight_gain_goal(weight_gain_goal);
		} else {
			std::cout << "weight lose per week (lb)? ";
			std::cin >> weight_lose_goal;
			user.set_weight_lose_goal(weight_lose_goal);
		}

		user.set_height(height_ft, height_in);
		user.set_weight(weight_lb);
	} else {
		std::cout << "height in cm? ";
		std::cin >> height_cm;
		std::cout << "weight in kg? ";
		std::cin >> weight_kg;

		if (weight_goal == ct::gain_weight) {
			std::cout << "weight gain per week (kg)? ";
			std::cin >> weight_gain_goal;
			user.set_weight_gain_goal(weight_gain_goal);
		} else {
			std::cout << "weight lose per week (kg)? ";
			std::cin >> weight_lose_goal;
			user.set_weight_lose_goal(weight_lose_goal);
		}

		user.set_height(height_cm);
		user.set_weight(weight_kg);
	}

	user.save();
}

int main() {
	ct::UserInfo user;

	if (user.need_info()) {
		prompt_user(user);
	} else {
		std::cout << "welcome back " << user.get_name() << std::endl;
	}

	try {
		std::cout << "you need to eat " << user.calculate_calories() << " every day" << std::endl;
	} catch (std::string &error) {
		std::cout << error << std::endl;
		std::cout << "your daily calorie needs cant be calculated" << std::endl;
	}

	return 0;
}
