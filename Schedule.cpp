//
// Created by tiago on 28-10-2023.
//

#include "Schedule.h"

bool operator==(const dayScheduleEntry& d1, const dayScheduleEntry& d2) {
    return (d1.UC_code == d2.UC_code and
            d1.class_code == d2.class_code and
            d1.start_hour == d2.start_hour and
            d1.duration == d2.duration and
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

bool Schedule::checkDayScheduleEntryConflict(const string &week_day, const dayScheduleEntry& entry) const{
    double e1_beginning_time = entry.start_hour;
    double e1_finishing_time = entry.start_hour + entry.duration;
    double e2_beginning_time, e2_finishing_time;

    if(entry.class_type != "T"){
        for(auto & it : schedule_.at(week_day)){
            e2_beginning_time = it.start_hour;
            e2_finishing_time = it.start_hour + it.duration;
            if(e1_beginning_time <= e2_finishing_time and e2_beginning_time <= e1_finishing_time){
                return true;
            }
        }
    }

    return false;
}

void Schedule::addSchedule(const Schedule& s){
    for(const auto & it_map_elem : s.schedule_){
        for(auto it_schedule_entry = it_map_elem.second.begin(); it_schedule_entry != it_map_elem.second.end(); it_schedule_entry++){
            this->addDayScheduleEntry(it_map_elem.first, *it_schedule_entry);
        }
    }
}

void Schedule::removeSchedule(const Schedule& s){
    for(const auto & it_map_elem : s.schedule_){
        for(auto it_schedule_entry = it_map_elem.second.begin(); it_schedule_entry != it_map_elem.second.end(); it_schedule_entry++){
            this->removeDayScheduleEntry(it_map_elem.first, *it_schedule_entry);
        }
    }
}

bool Schedule::checkScheduleConflict(const Schedule& s) const{
    for(const auto & it_map_elem : s.schedule_){
        for(auto it_schedule_entry = it_map_elem.second.begin(); it_schedule_entry != it_map_elem.second.end(); it_schedule_entry++){
            this->checkDayScheduleEntryConflict(it_map_elem.first, *it_schedule_entry);
        }
    }
}

/**
 * @brief This function prints the day schedule of a week.
 *
 * Receives a weekday and prints the schedule for the day.
 *
 * @param week_day Description of the first parameter.
 *
 *
 */

void Schedule::PrintDaySchedule(const string &week_day) const{
    cout << left  << week_day << endl;
    if (schedule_.at(week_day).empty()){
        cout << left << "No classes on this day" << endl;
    } else{
        cout << left  << setw(15) << "UC code" << setw(15) << "Class code" << setw(15) << "Start Time" << std::setw(15) << "Duration" << std::setw(15) << "Type" << std::endl;
        for (const auto& classSchedule : schedule_.at(week_day)) {
            cout << left << setw(15) << classSchedule.UC_code
                 << setw(15) << classSchedule.class_code
                 << setw(15) << classSchedule.start_hour
                 << setw(15) << classSchedule.duration
                 << setw(15) << classSchedule.class_type << endl;
        }
    }
}

void Schedule::PrintWeekSchedule() const{
    this->PrintDaySchedule("Monday");
    cout << endl;
    this->PrintDaySchedule("Tuesday");
    cout << endl;
    this->PrintDaySchedule("Wednesday");
    cout << endl;
    this->PrintDaySchedule("Thursday");
    cout << endl;
    this->PrintDaySchedule("Friday");
}

