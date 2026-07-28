#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <string>
#include <chrono>
#include <ctime>
#include <cstdint>

namespace datetime {

struct Date {
    int year;
    int month;
    int day;
};

struct Time {
    int hour;
    int minute;
    int second;
    int millisecond;
};

struct DateTime {
    Date date;
    Time time;
};

DateTime now();
DateTime from_timestamp(int64_t timestamp);
int64_t to_timestamp(const DateTime& dt);

std::string format(const DateTime& dt, const std::string& fmt = "%Y-%m-%d %H:%M:%S");
DateTime parse(const std::string& str, const std::string& fmt = "%Y-%m-%d %H:%M:%S");

bool is_leap_year(int year);
int days_in_month(int year, int month);
int day_of_week(const DateTime& dt);
int day_of_year(const DateTime& dt);

DateTime add_days(const DateTime& dt, int days);
DateTime add_months(const DateTime& dt, int months);
DateTime add_years(const DateTime& dt, int years);

int64_t diff_seconds(const DateTime& a, const DateTime& b);
int diff_days(const DateTime& a, const DateTime& b);

DateTime utc_now();

} // namespace datetime

#endif
