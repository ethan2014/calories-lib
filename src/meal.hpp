#ifndef MEAL_HPP
#define MEAL_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "food.hpp"

namespace ct {
namespace meal {

class Meal {
public:
	std::string name;
	
	std::vector<ct::food::FoodItem> foods;

	float calories();

	void add_food(ct::food::FoodItem);
};

extern std::unordered_map<std::string, Meal> known_meals;
//std::vector<Meal> known_meals;

void init();
void load_meals();
void save_meal(Meal m);

bool meal_exists(std::string name);

Meal get_meal(std::string name);

}
}

#endif
