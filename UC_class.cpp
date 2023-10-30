//
// Created by tiago on 28-10-2023.
//

#include "UC_class.h"

UC_class::UC_class(string& UC_name) :
        UC_name_(UC_name),
        enrolled_students_(),
        number_of_enrolled_students_(0),
        number_of_vacancies_(27),
        UC_class_schedule_() {}

UC_class::UC_class(const UC_class &other) {
    UC_name_ = other.UC_name_;
    enrolled_students_ = other.enrolled_students_;
    number_of_enrolled_students_ = other.number_of_enrolled_students_;
    number_of_vacancies_ = other.number_of_vacancies_;
    UC_class_schedule_ = other.UC_class_schedule_;
}

const string& UC_class::getUcName() const {
    return UC_name_;
}

void UC_class::getEnrolledStudents() const {
    for (const Student& student : enrolled_students_) {
        std::cout << "Student number: " << student.getIdNumber() << " Student name: " << student.getStudentName() << std::endl;
    }
}

bool UC_class::operator<(const UC_class &other) const {
    return UC_name_ < other.UC_name_;
}

void UC_class::getUcDaySchedule(const string& weekDay) const {
    UC_class_schedule_.getDaySchedule(weekDay);
}

void UC_class::getUcWeekSchedule() const {
    UC_class_schedule_.getWeekSchedule();
}

void UC_class::addUcSchedule(const string &weekDay, const dayScheduleEntry &someSchedule) {
    UC_class_schedule_.addClassSchedule(weekDay, someSchedule);
}

