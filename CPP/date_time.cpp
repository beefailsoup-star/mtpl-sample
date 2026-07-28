#include "date_time.h"
#include <sstream>
#include <iomanip>
#include <array>

namespace datetime {

DateTime now() {
    auto tp = std::chrono::system_clock::now();
    auto tt = std::chrono::system_clock::to_time_t(tp);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        tp.time_since_epoch()) % 1000;
    struct tm t;
    localtime_s(&t, &tt);
    return {
        {t.tm_year + 1900, t.tm_mon + 1, t.tm_mday},
        {t.tm_hour, t.tm_min, t.tm_sec, static_cast<int>(ms.count())}
    };
}

DateTime utc_now() {
    auto tp = std::chrono::system_clock::now();
    auto tt = std::chrono::system_clock::to_time_t(tp);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        tp.time_since_epoch()) % 1000;
    struct tm t;
    gmtime_s(&t, &tt);
    return {
        {t.tm_year + 1900, t.tm_mon + 1, t.tm_mday},
        {t.tm_hour, t.tm_min, t.tm_sec, static_cast<int>(ms.count())}
    };
}

DateTime from_timestamp(int64_t timestamp) {
    auto tp = std::chrono::system_clock::from_time_t(timestamp);
    auto tt = std::chrono::system_clock::to_time_t(tp);
    struct tm t;
    localtime_s(&t, &tt);
    return {
        {t.tm_year + 1900, t.tm_mon + 1, t.tm_mday},
        {t.tm_hour, t.tm_min, t.tm_sec, 0}
    };
}

int64_t to_timestamp(const DateTime& dt) {
    struct tm t = {};
    t.tm_year = dt.date.year - 1900;
    t.tm_mon = dt.date.month - 1;
    t.tm_mday = dt.date.day;
    t.tm_hour = dt.time.hour;
    t.tm_min = dt.time.minute;
    t.tm_sec = dt.time.second;
    return static_cast<int64_t>(std::mktime(&t));
}

std::string format(const DateTime& dt, const std::string& fmt) {
    struct tm t = {};
    t.tm_year = dt.date.year - 1900;
    t.tm_mon = dt.date.month - 1;
    t.tm_mday = dt.date.day;
    t.tm_hour = dt.time.hour;
    t.tm_min = dt.time.minute;
    t.tm_sec = dt.time.second;
    char buf[64];
    std::strftime(buf, sizeof(buf), fmt.c_str(), &t);
    return buf;
}

DateTime parse(const std::string& str, const std::string& fmt) {
    struct tm t = {};
    std::istringstream ss(str);
    ss >> std::get_time(&t, fmt.c_str());
    return {
        {t.tm_year + 1900, t.tm_mon + 1, t.tm_mday},
        {t.tm_hour, t.tm_min, t.tm_sec, 0}
    };
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int year, int month) {
    static const std::array<int, 12> days = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    if (month == 2 && is_leap_year(year)) return 29;
    return days[month - 1];
}

int day_of_week(const DateTime& dt) {
    struct tm t = {};
    t.tm_year = dt.date.year - 1900;
    t.tm_mon = dt.date.month - 1;
    t.tm_mday = dt.date.day;
    std::mktime(&t);
    return t.tm_wday;
}

int day_of_year(const DateTime& dt) {
    struct tm t = {};
    t.tm_year = dt.date.year - 1900;
    t.tm_mon = dt.date.month - 1;
    t.tm_mday = dt.date.day;
    std::mktime(&t);
    return t.tm_yday + 1;
}

DateTime add_days(const DateTime& dt, int days) {
    auto ts = to_timestamp(dt) + days * 86400;
    return from_timestamp(ts);
}

DateTime add_months(const DateTime& dt, int months) {
    DateTime result = dt;
    result.date.month += months;
    while (result.date.month > 12) { result.date.month -= 12; ++result.date.year; }
    while (result.date.month < 1) { result.date.month += 12; --result.date.year; }
    int max_day = days_in_month(result.date.year, result.date.month);
    if (result.date.day > max_day) result.date.day = max_day;
    return result;
}

DateTime add_years(const DateTime& dt, int years) {
    return add_months(dt, years * 12);
}

int64_t diff_seconds(const DateTime& a, const DateTime& b) {
    return to_timestamp(a) - to_timestamp(b);
}

int diff_days(const DateTime& a, const DateTime& b) {
    return static_cast<int>(diff_seconds(a, b) / 86400);
}

} // namespace datetime
