//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_SCHEDULE_H
#define AED_PROJECT_SCHEDULE_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

struct dayScheduleEntry {
    string UC_code;
    string class_code;
    double start_hour;
    double duration;
    string class_type;
};

bool operator==(const dayScheduleEntry& d1, const dayScheduleEntry& d2) {
    return (d1.UC_code == d2.UC_code &&
            d1.class_code == d2.class_code &&
            d1.start_hour == d2.start_hour &&
            d1.duration == d2.duration &&
            d1.class_type == d2.class_type);
}

class Schedule {
private:
    map<string , vector<dayScheduleEntry>> schedule_;

public:
    Schedule();
    Schedule(const Schedule& other);

    void addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);
    void removeDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);
    bool checkDayScheduleEntryConflict(const string &week_day, const dayScheduleEntry& entry); // Se houver conflito, return true
    void addClassSchedule(const string& weekDay, const dayScheduleEntry& someSchedule);
    void getDaySchedule(const std::string& weekDay) const ;
    void getWeekSchedule() const;

};



#endif //AED_PROJECT_SCHEDULE_H
