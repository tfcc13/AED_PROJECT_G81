//
// Created by tiago on 28-10-2023.
//

#include "Schedule.h"

Schedule::Schedule() {
    schedule =  {

            {"Monday", {}},
            {"Tuesday",{}},
            {"Wednesday",{}},
            {"Thursday",{}},
            {"Friday",{}}
    };
}
Schedule::Schedule(const Schedule &other) {
    schedule = other.schedule;
}

void Schedule::addClassSchedule(const std::string &weekDay, const classSchedule& someSchedule) {
    schedule[weekDay].emplace_back(someSchedule);
    std::sort(schedule[weekDay].begin(), schedule[weekDay].end(), [](const classSchedule& a, const classSchedule& b) {
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