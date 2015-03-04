#include <iostream>
#include <limits>

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

void list_meals() {
	if (!ct::day::current_day.has_meals()) {
		std::cout << "no meals eaten yet today" << std::endl;
		return;
	}

	std::vector<ct::meal::Meal> meals = ct::day::current_day.meals;

	for (auto meal : meals) {
		std::cout << "--------------------" << std::endl;
		std::cout << "meal name: " << meal.name << std::endl;
		std::cout << "total calories: " << meal.calories() << std::endl;

		for (auto food : meal.foods) {
			std::cout << "food: " << food.name() << std::endl;
			std::cout << "servings: " << food.servings << std::endl;
			std::cout << "calories: " << food.calories() << std::endl;
		}
	}
			
	std::cout << "--------------------" << std::endl;
	std::cout << "calories for today: " << ct::day::current_day.calories()
		  << " / " << ct::user::calculate_calories() << std::endl;
}

void new_food(std::string name) {
	ct::food::FoodInfo info;

	info.name = name;

	std::cout << "serving size? ";
	std::cin >> info[ct::food::serving_size];

	std::cout << "calories per serving? ";
	std::cin >> info[ct::food::calories];

	ct::food::save_food_info(info);
}

void add_meal() {
	int num_items = 0;
	std::string name;
	
	std::cout << "--------------------" << std::endl;
	std::cout << "how many food items? ";
	std::cin >> num_items;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "what is this meal called? ";
	std::getline(std::cin, name);

	ct::meal::Meal m;

	m.name = name;

	for (int i = 0; i < num_items; i++) {
		ct::food::FoodItem food;
		ct::food::FoodInfo info;
		int amount;

		std::cout << "name of item? ";
		std::getline(std::cin, name);

		if (!ct::food::food_info_exists(name)) {
			std::cout << "I dont know what that is yet, lets add it" << std::endl;
			new_food(name);
		}

		std::cout << "how many servings you eat? ";
		std::cin >> amount;

		info = ct::food::known_foods[name];
		food.info = info;
		food.servings = amount;

		m.add_food(food);
	}

	ct::day::current_day.add_meal(m);
}

void remove_meal() {
	std::string name;

	std::cout << "name of meal? ";
	std::getline(std::cin, name);
}

int main() {
	ct::init();
	
	if (ct::user::needs_user_data()) {
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

	int input;

	do {
		std::cout << "++++++++++++++++++++" << std::endl;
		std::cout << "what do now?" << std::endl;
		std::cout << "-1: quit" << std::endl;
		std::cout << "0: list todays meals" << std::endl;
		std::cout << "1: add new meal" << std::endl;
		std::cout << "2: remove meal" << std::endl;
		std::cout << "> ";

		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input == 0) {
			list_meals();
		} else if (input == 1) {
			add_meal();
		} else if (input == 2) {
			remove_meal();
		}
	} while (input != -1);

	std::cout << "goodbye!" << std::endl;
}
