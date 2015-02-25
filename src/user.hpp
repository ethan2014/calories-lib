#ifndef USER_INFO_HPP
#define USER_INFO_HPP

#include <string>
#include <fstream>

namespace ct {
namespace user {

const int calories_per_lb = 3500;
const int calories_per_kg = 7700;

const int max_name_length = 100;

const int no_answer = -1;

const int male = 0;
const int female = 1;

const int exercise_none = 0;
const int exercise_low = 1;
const int exercise_med = 2;
const int exercise_high = 3;
const int exercise_very_high = 4;

const int no_goal = 0;
const int lose_weight = 1;
const int gain_weight = 2;

const int imperial = 0;
const int metric = 1;

extern std::string name;

extern int sex;

extern int age;

extern int height_ft;
extern int height_in;
extern int height_cm;

extern int weight_lb;
extern int weight_kg;

extern int calories;

extern int exercise_level;

extern int weight_goal;
extern float weight_gain_goal;
extern float weight_lose_goal;

extern int measurement_system;

void init();
bool needs_user_data();

void set_name(std::string new_name);
void set_sex(int new_sex);
void set_age(int new_age);
void set_height(int new_ft, int new_in);
void set_height(int new_cm);
void set_weight(int new_weight);
void set_calories(int new_calories);
void set_exercise_level(int new_level);
void set_weight_goal(int new_goal);
void set_weight_gain_goal(float new_gain);
void set_weight_lose_goal(float new_lose);
void set_measurement_system(int new_system);

std::string get_name();
int get_sex();
int get_age();
int get_height_ft();
int get_height_in();
int get_height_cm();
int get_weight();
int get_calories();
int get_exercise_level();
int get_weight_goal();
int get_measurement_system();

void save();
void load();
	
/*
 * uses the The Mifflin St Jeor Equation to calculate BMR (Basal metabolic rate)
 */
int calculate_calories();

int weight_lb_to_kg();
int height_ft_to_cm();

}

}

#endif
