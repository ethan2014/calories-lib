#include "food.hpp"

namespace ct {
namespace food {

FoodInfo::FoodInfo() {
	// we will only set defaults for these very common nutrients,
	// other nutrients like cholesterol, potassium and the many different
	// vitamins and minerals will be added if needed
	nutrient_info[amount_per_serving] = no_info;
	nutrient_info[calories] = no_info;
	nutrient_info[fat] = no_info;
	nutrient_info[saturated_fat] = no_info;
	nutrient_info[mono_fat] = no_info;
	nutrient_info[poly_fat] = no_info;
	nutrient_info[trans_fat] = no_info;
	nutrient_info[carbs] = no_info;
	nutrient_info[protein] = no_info;
	nutrient_info[sugar] = no_info;
	nutrient_info[sodium] = no_info;

	category = no_category;

}

float FoodInfo::calculate_servings(float amount) {
	float per_serving = nutrient_info[amount_per_serving];

	if (per_serving == 0) {
		return 0;
	}

	return amount / per_serving;
}

void FoodItem::amount_consumed(float amount) {
	servings = info.calculate_servings(amount);
}

}
}
