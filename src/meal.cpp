#include "meal.hpp"

#include <iostream>

namespace ct {
namespace meal {

std::unordered_map<std::string, Meal> known_meals;

/*
 * functions in Meal class
 */

float Meal::calories() {
	float cal = 0;

	for (auto f : foods) {
		cal += f.calories();
	}
	
	return cal;
}

void Meal::add_food(ct::food::FoodItem f) {
	foods.push_back(f);
}

/*
 * functions global to meal namespace
 */

void init() {
	// load all the known meals from the hard drive
	load_meals();
}

void load_meals() {
	// TODO: fill the know_meals map with meals from our
	// known meals database
}

void save_meal(Meal m) {
	if (meal_exists(m.name)) {
		return;
	}

	known_meals[m.name] = m;
//	known_meals.push_back(m);

	// TODO: add this meal to the database so it will persist through
	// reboots of the app
}

bool meal_exists(std::string name) {
	for (auto it : known_meals) {
		if (it.first == name) {
			return true;
		}
	}

	return false;
}

Meal get_meal(std::string name) {
	for (auto it : known_meals) {
		if (it.first == name) {
			return it.second;
		}
	}

	throw std::string("error: meal of name `" + name + "' doesnt exist");
}

}
}
