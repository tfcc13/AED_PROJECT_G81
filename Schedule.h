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

struct classSchedule {
    double startHour;
    double duration;
    std::string classType;

};

class Schedule {
private:
    std::map<std::string , std::vector<classSchedule>> schedule;

public:
    Schedule();
    Schedule(const Schedule& other);

    void addClassSchedule(const std::string& weekDay, const classSchedule& someSchedule);
    void getDaySchedule(const std::string& weekDay) const ;
    void getWeekSchedule() const;

};



#endif //AED_PROJECT_SCHEDULE_H
