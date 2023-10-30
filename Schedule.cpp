//
// Created by tiago on 28-10-2023.
//

#include "Schedule.h"

Schedule::Schedule() {
    schedule_ =  {
            {"Monday", {}},
            {"Tuesday",{}},
            {"Wednesday",{}},
            {"Thursday",{}},
            {"Friday",{}}
    };
}

Schedule::Schedule(const Schedule &other) {
    schedule_ = other.schedule_;
}

void Schedule::addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){
    schedule_[week_day].emplace_back(entry);
    sort(schedule_[week_day].begin(), schedule_[week_day].end(), [](const dayScheduleEntry& a, const dayScheduleEntry& b) {
        return a.start_hour < b.start_hour;
    });
}

void Schedule::removeDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){



    sort(schedule_[week_day].begin(), schedule_[week_day].end(), [](const dayScheduleEntry& a, const dayScheduleEntry& b) {
        return a.start_hour < b.start_hour;
    });
}

void Schedule::addClassSchedule(const string &weekDay, const dayScheduleEntry& someSchedule) {
    dayScheduleEntry[weekDay].emplace_back(someSchedule);
    sort(dayScheduleEntry[weekDay].begin(), dayScheduleEntry[weekDay].end(), [](const dayScheduleEntry& a, const dayScheduleEntry& b) {
        return a.startHour < b.startHour;
    });
}

void Schedule::getDaySchedule(const std::string &weekDay) const {
    std::cout << std::left << weekDay << std::endl;
    std::cout << std::left << std::setw(15) << "Start Time" << std::setw(15) << "Duration" << std::setw(15) << "Type" << std::endl;
    for (const auto& classSchedule : schedule.at(weekDay)) {
        std::cout << std::left << std::setw(15) << classSchedule.startHour
                  << std::setw(15) << classSchedule.duration
                  << std::setw(15) << classSchedule.classType << std::endl;
    }
}

void Schedule::getWeekSchedule()  const {
    for (const auto& daySchedule : schedule) {
        getDaySchedule(daySchedule.first);
    }
}