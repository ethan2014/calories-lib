#ifndef USER_INFO_HPP
#define USER_INFO_HPP

#include <string>
#include <fstream>

namespace ct {

const int no_answer = -1;

const int male = 0;
const int female = 1;

const int exercise_none = 0;
const int exercise_low = 1;
const int exercise_med = 2;
const int exercise_high = 3;
const int exercise_very_high = 4;

const int lose_2 = 0;
const int lose_1 = 1;
const int stay_same = 2;
const int gain_1 = 3;
const int gain_2 = 4;

const int imperial = 0;
const int metric = 1;

class UserInfo {
public:
	UserInfo();

	void set_name(std::string new_name);
	void set_sex(int new_sex);
	void set_age(int new_age);
	void set_height(int new_ft, int new_in);
	void set_height(int new_cm);
	void set_weight(int new_weight);
	void set_calories(int new_calories);
	void set_exercise_level(int new_level);
	void set_weight_goal(int new_goal);
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

	void save(std::ofstream &out);
	void load(std::ifstream &in);
	
private:
	std::string name;

	int sex;

	int age;

	int height_ft;
	int height_in;
	int height_cm;

	int weight_lb;
	int weight_kg;

	int calories_needed;

	int exercise_level;

	int weight_goal;

	int measurement_system;
};

}

#endif
