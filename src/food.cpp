#include "food.hpp"

#include <unordered_map>

namespace ct {
namespace food {

std::unordered_map<std::string, FoodInfo> known_foods;

/*
 * functions in FoodInfo class
 */

FoodInfo::FoodInfo() {
	// we will only set defaults for these very common nutrients,
	// other nutrients like cholesterol, potassium and the many different
	// vitamins and minerals will be added if needed
	nutrients[serving_size] = no_info;
	nutrients[calories] = no_info;
	nutrients[fat] = no_info;
	nutrients[saturated_fat] = no_info;
	nutrients[mono_fat] = no_info;
	nutrients[poly_fat] = no_info;
	nutrients[trans_fat] = no_info;
	nutrients[carbs] = no_info;
	nutrients[protein] = no_info;
	nutrients[sugar] = no_info;
	nutrients[sodium] = no_info;

	name = no_name;

	category = no_category;

}

float FoodInfo::calculate_servings(float amount) {
	float size = nutrients[serving_size];

	if (size == 0) {
		return 0;
	}

	if (size == no_info || size < 0) {
		throw std::string("error: serving size cant be < 0");
	}

	return amount / size;
}


//float& FoodInfo::operator[](std::string name) {
//	return nutrients[name];
//}

/*
 * functions in FoodItem class
 */

FoodItem::FoodItem() {
	servings = no_info;
}

void FoodItem::amount_consumed(float amount) {
	servings = info.calculate_servings(amount);
}

float FoodItem::calories() {
	if (servings == no_info || servings <= 0) {
		throw std::string("error: servings cant be < 0");
	}

	return servings * info.nutrients[ct::food::calories];
}

/*
 * functions in global to foods namespace
 */

void init() {
	load_food_info();
}

void load_food_info() {
	// TODO: fill the known_foods vector with food info from
	// our database of known food info

	// for now, add hard coded test foods

	FoodInfo f;

	f.name = "milk";
	f.nutrients[serving_size] = 1;
	f.nutrients[calories] = 150;
	f.nutrients[fat] = 8;
	f.nutrients[saturated_fat] = 5;
	f.nutrients[mono_fat] = 2.5;
	f.nutrients[cholesterol] = 35;
	f.nutrients[sodium] = 120;
	f.nutrients[potassium] = 380;
	f.nutrients[carbs] = 12;
	f.nutrients[sugar] = 11;
	f.nutrients[protein] = 8;
	known_foods[f.name] = f;
	
}

void save_food_info(FoodInfo f) {
	if (food_info_exists(f.name)) {
		return;
	}

	known_foods[f.name] = f;

	// TODO: add this food info to the food info database
}

bool food_info_exists(std::string name) {
	for (auto it : known_foods) {
		if (it.first == name) {
			return true;
		}
	}

	return false;
}

FoodInfo get_food_info(std::string name) {
	for (auto it : known_foods) {
		if (it.first == name) {
			return it.second;
		}
	}

	throw std::string("error: food of name `" + name + "' doesnt exist");
}

}
}
