#ifndef DAY_HPP
#define DAY_HPP

#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include "meal.hpp"

namespace ct {
namespace day {

Day current_day;
Day today;

class Day {
public:
	boost::gregorian::date date;

	int calories;

	std::vector<Meal> meals;

	void add_meal(Meal m);
};

void init_today();
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
