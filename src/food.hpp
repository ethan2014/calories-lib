#ifndef FOOD_HPP
#define FOOD_HPP

#include <unordered_map>

namespace ct {
namespace food {

const std::string no_name = "N/A";
const std::string serving_size = "serving size";
const std::string calories = "calories";
const std::string fat = "fat";
const std::string saturated_fat = "saturated fat";
const std::string mono_fat = "mono fat";
const std::string poly_fat = "poly fat";
const std::string trans_fat = "trans fat";
const std::string carbs = "carbs";
const std::string protein = "protein";
const std::string sugar = "sugar";
const std::string cholesterol = "cholesterol";
const std::string sodium = "sodium";
const std::string potassium = "potassium";
const std::string vitamin_a = "vitamin a";
const std::string vitamin_c = "vitamin c";
const std::string calcium = "calcium";
const std::string iron = "iron";
const std::string vitamin_d = "vitamin d";
const std::string vitamin_e = "vitamin e";
const std::string vitamin_k = "vitamin k";
const std::string thiamin = "thiamin";
const std::string riboflavin = "riboflavin";
const std::string niacin = "niacin";
const std::string vitamin_b6 = "vitamin b6";
const std::string folate = "folate";
const std::string vitamin_b12 = "vitamin b12";
const std::string biotin = "biotin";
const std::string pantothenic_acid = "pantothenic acid";
const std::string phosphorus = "phosphorus";
const std::string iodine = "iodine";
const std::string magnesium = "magnesium";
const std::string zinc = "zinc";
const std::string selenium = "selenium";
const std::string copper = "copper";
const std::string manganese = "manganese";
const std::string chromium = "chromium";
const std::string molybdenum = "molybdenum";
const std::string chloride = "chloride";

const float no_info = 0;

const int no_category = -1;
const int vegetable = 0;
const int fruit = 1;
const int grain = 2;
const int dairy = 3;
const int protein_foods = 4;

class FoodInfo {
public:
	std::string name;
	
	std::unordered_map<std::string, float> nutrients;

	int category;

	FoodInfo();

	float calculate_servings(float amount);

//	float& operator[](std::string name);
};

class FoodItem {
public:
	FoodInfo info;

	float servings;

	FoodItem();
	
	void amount_consumed(float amount);

	float calories();
};

extern std::unordered_map<std::string, FoodInfo> known_foods;

void init();
void load_food_info();
void save_food_info(FoodInfo f);

bool food_info_exists(std::string name);

FoodInfo get_food_info(std::string name);

}
}

#endif
