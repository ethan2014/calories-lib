#include "day.hpp"

namespace ct {
namespace day {

Day current_day;
Day today;

// only used for testing purposes before db is implemented
std::vector<Day> test_days;

/*
 * functions in Day class
 */

void Day::add_meal(ct::meal::Meal m) {
	meals.push_back(m);
}

float Day::calories() {
	float cal = 0;

	for (auto m : meals) {
		cal += m.calories();
	}

	return cal;
}

bool Day::has_meals() {
	return meals.size() != 0;
}

/*
 * functions global to day namespace
 */

void init() {
	boost::gregorian::date today_date(boost::gregorian::day_clock::local_day());

	if (day_exists(today_date)) {
		// today is already in our database, load it
		today = get_day(today_date);
	} else {
		// first time opening the app today
		today.date = today_date;
		save_today();
	}

	// the app will always start on today
	current_day = today;
}

void save_day(Day day) {
	// TODO: add this day to our database
	test_days.push_back(day);
}

void save_today() {
	save_day(today);
}

void save_current_day() {
	save_day(current_day);
}

void set_to_today() {
	current_day = today;
}

void set_current_day(Day d) {
	current_day = d;
}

std::vector<Day> list_days() {
	// TODO: load all days from database
	std::vector<Day> ret;

	
	
	return ret;
}

Day get_day(boost::gregorian::date date) {
	for (Day d : list_days()) {
		if (d.date == date) {
			return d;
		}
	}

	throw std::string("error: no day for given date");
}

bool day_exists(boost::gregorian::date date) {
	for (const Day &d : list_days()) {
		if (d.date == date) {
			return true;
		}
	}

	return false;
}

}
}
