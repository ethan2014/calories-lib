#ifndef MEAL_HPP
#define MEAL_HPP

#include "food.hpp"

namespace ct {
namespace meal {

class Meal {
	std::vector<ct::food::FoodItem> foods;
};

std::vector<Meal> known_meals;

void init();
void save_meal(Meal m);

bool meal_exists(std::string name);

Meal get_meal(std::string name);

}
}

#endif
