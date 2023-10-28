//
// Created by tiago on 28-10-2023.
//

#include "UC.h"

UC::UC(std::string &name) {
    uc_name = name;
}

UC::UC(const UC &other) {
    uc_name = other.uc_name;
    enrolled_students = other.enrolled_students;
    uc_schedule = other.uc_schedule;
}

const std::string& UC::getUcName() const {

    return uc_name;
}

void UC::getEnrolledStudents() const {
    for (Student student : enrolled_students) {
        std::cout << "Student number: " << student.getIdNumber() << " Student name: " << student.getStudentName() << std::endl;
    }
}

bool UC::operator<(const UC &other) const {
    return uc_name < other.uc_name;
}

void UC::getUcDaySchedule(const std::string& weekDay) const {
    uc_schedule.getDaySchedule(weekDay);
}

void UC::getUcWeekSchedule() const {
    uc_schedule.getWeekSchedule();
}

void UC::addUcSchedule(const std::string &weekDay, const classSchedule &someSchedule) {
    uc_schedule.addClassSchedule(weekDay, someSchedule);
}