//
// Created by tiago on 28-10-2023.
//

#include "Schedule.h"

bool operator==(const dayScheduleEntry& d1, const dayScheduleEntry& d2) {
    return (d1.UC_code == d2.UC_code &&
            d1.class_code == d2.class_code &&
            d1.start_hour == d2.start_hour &&
            d1.duration == d2.duration &&
            d1.class_type == d2.class_type);
}

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
    for(auto it = schedule_[week_day].begin(); it != schedule_[week_day].end(); it++){
        if(*it == entry){
            schedule_[week_day].erase(it);
        }
    }
    sort(schedule_[week_day].begin(), schedule_[week_day].end(), [](const dayScheduleEntry& a, const dayScheduleEntry& b) {
        return a.start_hour < b.start_hour;
    });
}

bool Schedule::checkDayScheduleEntryConflict(const string &week_day, const dayScheduleEntry& entry){
    double e1_beginning_time = entry.start_hour;
    double e1_finishing_time = entry.start_hour + entry.duration;
    double e2_beginning_time, e2_finishing_time;

    for(auto it = schedule_[week_day].begin(); it != schedule_[week_day].end(); it++){
        e2_beginning_time = it->start_hour;
        e2_finishing_time = it->start_hour + it->duration;
        if(e1_beginning_time <= e2_finishing_time and e2_beginning_time <= e1_finishing_time){
            return true;
        }
    }
    return false;
}

void Schedule::getDaySchedule(const std::string &weekDay) const {
    std::cout << std::left << weekDay << std::endl;
    std::cout << std::left << std::setw(15) << "Start Time" << std::setw(15) << "Duration" << std::setw(15) << "Type" << std::endl;
    for (const auto& classSchedule : schedule_.at(weekDay)) {
        std::cout << std::left << std::setw(15) << classSchedule.start_hour
                  << std::setw(15) << classSchedule.duration
                  << std::setw(15) << classSchedule.class_type << std::endl;
    }
}

void Schedule::getWeekSchedule()  const {
    for (const auto& daySchedule : schedule_) {
        getDaySchedule(daySchedule.first);
    }
}