#ifndef DAY_HPP
#define DAY_HPP

#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include "meal.hpp"

namespace ct {
namespace day {

class Day {
public:
	boost::gregorian::date date;

	std::vector<ct::meal::Meal> meals;

	void add_meal(ct::meal::Meal m);

	float calories();

	bool has_meals();
};

extern Day current_day;
extern Day today;

void init();
void save_day(Day day);
void save_today();
void save_current_day();
void set_to_today();

std::vector<Day> list_days();

Day get_day(boost::gregorian::date date);

bool day_exists(boost::gregorian::date date);

}
}

#endif
