#include "food.hpp"

#include <fstream>
#include <unordered_map>

#include <jsoncpp/json/json.h>

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

unsigned int FoodInfo::get_id() {
	std::hash<std::string> hash;
	return (unsigned int) hash(name);
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


float& FoodInfo::operator[](std::string name) {
	return nutrients[name];
}

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

std::string FoodItem::name() {
	return info.name;
}

/*
 * functions in global to foods namespace
 */



void init() {
	// load all known foods from the hard drive
	load_food_info();
}

static FoodInfo parse_food(const Json::Value item) {
	FoodInfo ret;

	ret.id = item["id"].asUInt();
	ret.category = item["category"].asInt();
	ret.name = item["name"].asString();
	
	Json::Value nutrition = item["nutrition"];
	for (auto const& id : nutrition.getMemberNames()) {
		ret.nutrients[id] = nutrition[id].asFloat();
	}

	return ret;
}

void load_food_info() {
	Json::Value root;
	Json::Reader reader;
	
	std::ifstream in("../data/food.json", std::ifstream::binary);

	bool success = reader.parse(in, root, false);

	if (!success) {
		throw std::string(reader.getFormatedErrorMessages());
	}

	Json::Value array = root["foods"];

	for (unsigned int i = 0; i < array.size(); i++) {
		FoodInfo food = parse_food(array[i]);
		known_foods[food.name] = food;
	}
}

void save_food_info(FoodInfo f) {
	if (food_info_exists(f.name)) {
		return;
	}

	known_foods[f.name] = f;

	Json::Value root;
	Json::Reader reader;
	Json::StyledStreamWriter writer;
	
	std::ifstream in("../data/food.json", std::ifstream::binary);

	bool success = reader.parse(in, root, false);

	if (!success) {
		throw std::string(reader.getFormatedErrorMessages());
	}

	Json::Value array = root["foods"];
	Json::Value new_item;
	Json::Value nutrients;

	new_item["id"] = f.id;
	new_item["name"] = f.name;
	new_item["category"] = f.category;

	for (auto it : f.nutrients) {
		nutrients[it.first] = it.second;
	}

	new_item["nutrition"] = nutrients;

	root["foods"].append(new_item);

	in.close();
	std::ofstream out("../data/food.json");
	writer.write(out, root);
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
